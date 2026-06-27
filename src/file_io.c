#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"

/* Static helper functions for safe line reading and parsing */

/**
 * @brief Strips trailing carriage return and newline characters from a string.
 * @param str The string to strip.
 */
static void strip_newline(char *str) {
  size_t len = strlen(str);
  while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
    str[len - 1] = '\0';
    len--;
  }
}

/**
 * @brief Reads a line from a file and strips the newline.
 * @param f The file pointer.
 * @param dest The destination buffer.
 * @param max_len The maximum length of the destination buffer.
 * @return 1 on success, 0 on failure.
 */
static int read_line_file(FILE *f, char *dest, size_t max_len) {
  if (fgets(dest, (int)max_len, f) == NULL) {
    return 0;
  }
  strip_newline(dest);
  return 1;
}

/**
 * @brief Reads an integer from the next line of a file.
 * @param f The file pointer.
 * @param out The pointer to store the parsed integer.
 * @return 1 on success, 0 on failure.
 */
static int read_int_file(FILE *f, int *out) {
  char buf[128];
  if (!read_line_file(f, buf, sizeof(buf))) {
    return 0;
  }
  char *endptr;
  long val = strtol(buf, &endptr, 10);
  if (endptr == buf || *endptr != '\0') {
    return 0;
  }
  *out = (int)val;
  return 1;
}

/**
 * @brief Reads a float from the next line of a file.
 * @param f The file pointer.
 * @param out The pointer to store the parsed float.
 * @return 1 on success, 0 on failure.
 */
static int read_float_file(FILE *f, float *out) {
  char buf[128];
  if (!read_line_file(f, buf, sizeof(buf))) {
    return 0;
  }
  char *endptr;
  double val = strtod(buf, &endptr);
  if (endptr == buf || *endptr != '\0') {
    return 0;
  }
  *out = (float)val;
  return 1;
}

static int is_file_non_empty(const char *path) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    return 0;
  }
  if (fseek(f, 0, SEEK_END) != 0) {
    fclose(f);
    return 0;
  }
  long size = ftell(f);
  fclose(f);
  return size > 0 ? 1 : 0;
}

/**
 * @brief Performs the transactional rename of active and backup database files.
 * Removes the old backup if it exists, renames active to backup, and promotes
 * temp to active.
 * @param active_path The path to the active file.
 * @param tmp_path The path to the temp file.
 * @param bak_path The path to the backup file.
 * @return 1 on success, 0 on failure.
 */
static int commit_transaction(const char *active_path, const char *tmp_path,
                              const char *bak_path) {
  int active_existed = 0;
  FILE *f = fopen(active_path, "r");
  if (f != NULL) {
    active_existed = 1;
    fclose(f);
    remove(bak_path);
    if (rename(active_path, bak_path) != 0) {
      return 0;
    }
  }
  remove(active_path);
  if (rename(tmp_path, active_path) != 0) {
    if (active_existed != 0) {
      (void)rename(bak_path, active_path);
    }
    return 0;
  }
  return 1;
}

/**
 * @brief Verifies if the active file exists and is not empty. If missing or
 * empty, copies backup to active.
 * @param active_path The path to the active file.
 * @param bak_path The path to the backup file.
 * @return 1 if active file is ready or restored, 0 if backup recovery was
 * attempted and failed or files do not exist.
 */
static int ensure_active_file(const char *active_path, const char *bak_path) {
  FILE *f = fopen(active_path, "r");
  if (f != NULL) {
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    if (size > 0) {
      return 1;
    }
  }

  FILE *fbak = fopen(bak_path, "r");
  if (fbak != NULL) {
    fclose(fbak);
    printf("Warning: Active database file '%s' was missing or corrupt. "
           "Restoring from backup '%s'.\n",
           active_path, bak_path);
    remove(active_path);

    FILE *src = fopen(bak_path, "r");
    if (src == NULL) {
      return 0;
    }
    FILE *dst = fopen(active_path, "w");
    if (dst == NULL) {
      fclose(src);
      return 0;
    }
    int ch;
    while ((ch = fgetc(src)) != EOF) {
      if (fputc(ch, dst) == EOF) {
        fclose(src);
        fclose(dst);
        return 0;
      }
    }
    fclose(src);
    fclose(dst);
    return 1;
  }
  return 0;
}

/* Static internal loader functions */

/**
 * @brief Internal helper to load products from a given file.
 */
static int load_products_internal(Product products[], int *product_count,
                                  const char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    *product_count = 0;
    return 1;
  }
  int count = 0;
  if (!read_int_file(f, &count)) {
    fclose(f);
    return 0;
  }
  if (count < 0 || count > MAX_PRODUCTS) {
    fclose(f);
    return 0;
  }
  for (int i = 0; i < count; i++) {
    Product p;
    memset(&p, 0, sizeof(Product));
    if (!read_int_file(f, &p.product_id) ||
        !read_line_file(f, p.product_name, sizeof(p.product_name)) ||
        !read_line_file(f, p.category, sizeof(p.category)) ||
        !read_line_file(f, p.brand, sizeof(p.brand)) ||
        !read_float_file(f, &p.price) || !read_int_file(f, &p.stock_quantity)) {
      fclose(f);
      return 0;
    }
    products[i] = p;
  }
  *product_count = count;
  fclose(f);
  return 1;
}

/**
 * @brief Internal helper to load bundles from a given file.
 */
static int load_bundles_internal(Bundle bundles[], int *bundle_count,
                                 const char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    *bundle_count = 0;
    return 1;
  }
  int count = 0;
  if (!read_int_file(f, &count)) {
    fclose(f);
    return 0;
  }
  if (count < 0 || count > MAX_BUNDLES) {
    fclose(f);
    return 0;
  }
  for (int i = 0; i < count; i++) {
    Bundle b;
    memset(&b, 0, sizeof(Bundle));
    if (!read_int_file(f, &b.bundle_id) ||
        !read_line_file(f, b.bundle_name, sizeof(b.bundle_name)) ||
        !read_float_file(f, &b.discount_rate) ||
        !read_float_file(f, &b.bundle_price) ||
        !read_int_file(f, &b.product_count)) {
      fclose(f);
      return 0;
    }
    if (b.product_count < 0 || b.product_count > MAX_BUNDLE_ITEMS) {
      fclose(f);
      return 0;
    }
    for (int j = 0; j < b.product_count; j++) {
      if (!read_int_file(f, &b.product_ids[j])) {
        fclose(f);
        return 0;
      }
    }
    bundles[i] = b;
  }
  *bundle_count = count;
  fclose(f);
  return 1;
}

/**
 * @brief Internal helper to load orders from a given file.
 */
static int load_orders_internal(Order orders[], int *order_count,
                                const char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    *order_count = 0;
    return 1;
  }
  int count = 0;
  if (!read_int_file(f, &count)) {
    fclose(f);
    return 0;
  }
  if (count < 0 || count > MAX_ORDERS) {
    fclose(f);
    return 0;
  }
  for (int i = 0; i < count; i++) {
    Order o;
    memset(&o, 0, sizeof(Order));
    if (!read_int_file(f, &o.order_id) ||
        !read_line_file(f, o.customer_name, sizeof(o.customer_name)) ||
        !read_int_file(f, &o.item_id) || !read_int_file(f, &o.is_bundle) ||
        !read_int_file(f, &o.quantity) || !read_float_file(f, &o.total_price) ||
        !read_line_file(f, o.order_date, sizeof(o.order_date))) {
      fclose(f);
      return 0;
    }
    orders[i] = o;
  }
  *order_count = count;
  fclose(f);
  return 1;
}

/**
 * @brief Internal helper to load admin credentials from a given file.
 */
static int load_admin_internal(AdminCredentials *admin, const char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    admin->is_setup = 0;
    memset(admin->username, 0, sizeof(admin->username));
    memset(admin->password, 0, sizeof(admin->password));
    return 1;
  }
  AdminCredentials a;
  memset(&a, 0, sizeof(AdminCredentials));
  if (!read_line_file(f, a.username, sizeof(a.username)) ||
      !read_line_file(f, a.password, sizeof(a.password))) {
    fclose(f);
    return 0;
  }
  a.is_setup = 1;
  *admin = a;
  fclose(f);
  return 1;
}

/* Public API Implementations */

int save_database(const Product products[], int product_count,
                  const Bundle bundles[], int bundle_count,
                  const Order orders[], int order_count,
                  const AdminCredentials *admin) {
  if (products == NULL || product_count < 0 || product_count > MAX_PRODUCTS) {
    return 0;
  }
  if (bundles == NULL || bundle_count < 0 || bundle_count > MAX_BUNDLES) {
    return 0;
  }
  if (orders == NULL || order_count < 0 || order_count > MAX_ORDERS) {
    return 0;
  }
  if (admin == NULL) {
    return 0;
  }

  /* 1. Write Products to products.tmp */
  FILE *fp = fopen("products.tmp", "w");
  if (fp == NULL) {
    return 0;
  }
  fprintf(fp, "%d\n", product_count);
  for (int i = 0; i < product_count; i++) {
    fprintf(fp, "%d\n", products[i].product_id);
    fprintf(fp, "%s\n", products[i].product_name);
    fprintf(fp, "%s\n", products[i].category);
    fprintf(fp, "%s\n", products[i].brand);
    fprintf(fp, "%.2f\n", (double)products[i].price);
    fprintf(fp, "%d\n", products[i].stock_quantity);
  }
  fclose(fp);
  if (!is_file_non_empty("products.tmp")) {
    remove("products.tmp");
    return 0;
  }

  /* 2. Write Bundles to bundles.tmp */
  FILE *fb = fopen("bundles.tmp", "w");
  if (fb == NULL) {
    remove("products.tmp");
    return 0;
  }
  fprintf(fb, "%d\n", bundle_count);
  for (int i = 0; i < bundle_count; i++) {
    fprintf(fb, "%d\n", bundles[i].bundle_id);
    fprintf(fb, "%s\n", bundles[i].bundle_name);
    fprintf(fb, "%.4f\n", (double)bundles[i].discount_rate);
    fprintf(fb, "%.2f\n", (double)bundles[i].bundle_price);
    fprintf(fb, "%d\n", bundles[i].product_count);
    for (int j = 0; j < bundles[i].product_count; j++) {
      fprintf(fb, "%d\n", bundles[i].product_ids[j]);
    }
  }
  fclose(fb);
  if (!is_file_non_empty("bundles.tmp")) {
    remove("products.tmp");
    remove("bundles.tmp");
    return 0;
  }

  /* 3. Write Orders to orders.tmp */
  FILE *fo = fopen("orders.tmp", "w");
  if (fo == NULL) {
    remove("products.tmp");
    remove("bundles.tmp");
    return 0;
  }
  fprintf(fo, "%d\n", order_count);
  for (int i = 0; i < order_count; i++) {
    fprintf(fo, "%d\n", orders[i].order_id);
    fprintf(fo, "%s\n", orders[i].customer_name);
    fprintf(fo, "%d\n", orders[i].item_id);
    fprintf(fo, "%d\n", orders[i].is_bundle);
    fprintf(fo, "%d\n", orders[i].quantity);
    fprintf(fo, "%.2f\n", (double)orders[i].total_price);
    fprintf(fo, "%s\n", orders[i].order_date);
  }
  fclose(fo);
  if (!is_file_non_empty("orders.tmp")) {
    remove("products.tmp");
    remove("bundles.tmp");
    remove("orders.tmp");
    return 0;
  }

  /* 4. Write Admin credentials to admin.tmp */
  FILE *fa = fopen("admin.tmp", "w");
  if (fa == NULL) {
    remove("products.tmp");
    remove("bundles.tmp");
    remove("orders.tmp");
    return 0;
  }
  if (admin->username[0] == '\0') {
    FILE *f_exist = fopen("admin.txt", "r");
    if (f_exist != NULL) {
      char temp_user[MAX_USERNAME_LEN] = {0};
      char temp_pass[(MAX_PASSWORD_LEN * 2) + 2] = {0};
      if (fgets(temp_user, (int)sizeof(temp_user), f_exist) != NULL &&
          fgets(temp_pass, (int)sizeof(temp_pass), f_exist) != NULL) {
        fprintf(fa, "%s", temp_user);
        fprintf(fa, "%s", temp_pass);
      } else {
        fprintf(fa, "\n\n");
      }
      fclose(f_exist);
    } else {
      fprintf(fa, "\n\n");
    }
  } else {
    fprintf(fa, "%s\n", admin->username);
    fprintf(fa, "%s\n", admin->password);
  }
  fclose(fa);
  if (!is_file_non_empty("admin.tmp")) {
    remove("products.tmp");
    remove("bundles.tmp");
    remove("orders.tmp");
    remove("admin.tmp");
    return 0;
  }

  /* 5. Commit transactions for all database files */
  int success = 1;
  if (!commit_transaction("products.txt", "products.tmp", "products.bak")) {
    success = 0;
  }
  if (!commit_transaction("bundles.txt", "bundles.tmp", "bundles.bak")) {
    success = 0;
  }
  if (!commit_transaction("orders.txt", "orders.tmp", "orders.bak")) {
    success = 0;
  }
  if (!commit_transaction("admin.txt", "admin.tmp", "admin.bak")) {
    success = 0;
  }

  return success;
}

int load_database(Product products[], int *product_count, Bundle bundles[],
                  int *bundle_count, Order orders[], int *order_count,
                  AdminCredentials *admin) {
  if (products == NULL || product_count == NULL || bundles == NULL ||
      bundle_count == NULL || orders == NULL || order_count == NULL ||
      admin == NULL) {
    return 0;
  }

  int overall_success = 1;

  /* 1. Load Products */
  (void)ensure_active_file("products.txt", "products.bak");
  if (!load_products_internal(products, product_count, "products.txt")) {
    printf(
        "Warning: 'products.txt' load failed or corrupt. Restoring backup.\n");
    remove("products.txt");
    FILE *src = fopen("products.bak", "r");
    if (src != NULL) {
      FILE *dst = fopen("products.txt", "w");
      if (dst != NULL) {
        int ch;
        while ((ch = fgetc(src)) != EOF) {
          (void)fputc(ch, dst);
        }
        fclose(dst);
      }
      fclose(src);
    }
    if (!load_products_internal(products, product_count, "products.txt")) {
      *product_count = 0;
      overall_success = 0;
    }
  }

  /* 2. Load Bundles */
  (void)ensure_active_file("bundles.txt", "bundles.bak");
  if (!load_bundles_internal(bundles, bundle_count, "bundles.txt")) {
    printf(
        "Warning: 'bundles.txt' load failed or corrupt. Restoring backup.\n");
    remove("bundles.txt");
    FILE *src = fopen("bundles.bak", "r");
    if (src != NULL) {
      FILE *dst = fopen("bundles.txt", "w");
      if (dst != NULL) {
        int ch;
        while ((ch = fgetc(src)) != EOF) {
          (void)fputc(ch, dst);
        }
        fclose(dst);
      }
      fclose(src);
    }
    if (!load_bundles_internal(bundles, bundle_count, "bundles.txt")) {
      *bundle_count = 0;
      overall_success = 0;
    }
  }

  /* 3. Load Orders */
  (void)ensure_active_file("orders.txt", "orders.bak");
  if (!load_orders_internal(orders, order_count, "orders.txt")) {
    printf("Warning: 'orders.txt' load failed or corrupt. Restoring backup.\n");
    remove("orders.txt");
    FILE *src = fopen("orders.bak", "r");
    if (src != NULL) {
      FILE *dst = fopen("orders.txt", "w");
      if (dst != NULL) {
        int ch;
        while ((ch = fgetc(src)) != EOF) {
          (void)fputc(ch, dst);
        }
        fclose(dst);
      }
      fclose(src);
    }
    if (!load_orders_internal(orders, order_count, "orders.txt")) {
      *order_count = 0;
      overall_success = 0;
    }
  }

  /* 4. Load Admin Credentials */
  (void)ensure_active_file("admin.txt", "admin.bak");
  if (!load_admin_internal(admin, "admin.txt")) {
    printf("Warning: 'admin.txt' load failed or corrupt. Restoring backup.\n");
    remove("admin.txt");
    FILE *src = fopen("admin.bak", "r");
    if (src != NULL) {
      FILE *dst = fopen("admin.txt", "w");
      if (dst != NULL) {
        int ch;
        while ((ch = fgetc(src)) != EOF) {
          (void)fputc(ch, dst);
        }
        fclose(dst);
      }
      fclose(src);
    }
    if (!load_admin_internal(admin, "admin.txt")) {
      admin->is_setup = 0;
      memset(admin->username, 0, sizeof(admin->username));
      memset(admin->password, 0, sizeof(admin->password));
      overall_success = 0;
    }
  }

  return overall_success;
}
