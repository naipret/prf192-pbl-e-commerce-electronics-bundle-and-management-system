#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "file_io.h"
#include "types.h"

static void clean_test_files(void) {
  unlink("products.txt");
  unlink("products.tmp");
  unlink("products.bak");
  unlink("bundles.txt");
  unlink("bundles.tmp");
  unlink("bundles.bak");
  unlink("orders.txt");
  unlink("orders.tmp");
  unlink("orders.bak");
  unlink("admin.txt");
  unlink("admin.tmp");
  unlink("admin.bak");
}

static void test_save_load_success(void) {
  printf("Running test_save_load_success...\n");
  clean_test_files();

  // 1. Prepare sample data
  Product products[MAX_PRODUCTS];
  int product_count = 2;
  memset(products, 0, sizeof(products));
  products[0].product_id = 101;
  strcpy(products[0].product_name, "Smartphone X");
  strcpy(products[0].category, "Phone");
  strcpy(products[0].brand, "Apple");
  products[0].price = 899.99F;
  products[0].stock_quantity = 45;

  products[1].product_id = 102;
  strcpy(products[1].product_name, "Laptop Y");
  strcpy(products[1].category, "Laptop");
  strcpy(products[1].brand, "Dell");
  products[1].price = 1299.50F;
  products[1].stock_quantity = 15;

  Bundle bundles[MAX_BUNDLES];
  int bundle_count = 1;
  memset(bundles, 0, sizeof(bundles));
  bundles[0].bundle_id = 201;
  strcpy(bundles[0].bundle_name, "Ultimate Bundle");
  bundles[0].discount_rate = 0.10F;
  bundles[0].bundle_price = 1979.54F;
  bundles[0].product_count = 2;
  bundles[0].product_ids[0] = 101;
  bundles[0].product_ids[1] = 102;

  Order orders[MAX_ORDERS];
  int order_count = 1;
  memset(orders, 0, sizeof(orders));
  orders[0].order_id = 301;
  strcpy(orders[0].customer_name, "John Doe");
  orders[0].item_id = 101;
  orders[0].is_bundle = 0;
  orders[0].quantity = 2;
  orders[0].total_price = 1799.98F;
  strcpy(orders[0].order_date, "2026-06-27");

  AdminCredentials admin;
  memset(&admin, 0, sizeof(admin));
  strcpy(admin.username, "admin_user");
  strcpy(admin.password, "securesaver123");
  admin.is_setup = 1;

  // 2. Save database
  int save_res = save_database(products, product_count, bundles, bundle_count, orders, order_count, &admin);
  assert(save_res == 1);

  // Verify that the files exist and are not empty
  FILE *f = fopen("products.txt", "r");
  assert(f != NULL);
  fclose(f);

  // 3. Load database back into empty arrays
  Product loaded_products[MAX_PRODUCTS];
  int loaded_product_count = 0;
  Bundle loaded_bundles[MAX_BUNDLES];
  int loaded_bundle_count = 0;
  Order loaded_orders[MAX_ORDERS];
  int loaded_order_count = 0;
  AdminCredentials loaded_admin;
  memset(loaded_products, 0, sizeof(loaded_products));
  memset(loaded_bundles, 0, sizeof(loaded_bundles));
  memset(loaded_orders, 0, sizeof(loaded_orders));
  memset(&loaded_admin, 0, sizeof(loaded_admin));

  int load_res = load_database(loaded_products, &loaded_product_count,
                               loaded_bundles, &loaded_bundle_count,
                               loaded_orders, &loaded_order_count,
                               &loaded_admin);
  assert(load_res == 1);

  // 4. Assert correctness
  assert(loaded_product_count == 2);
  assert(loaded_products[0].product_id == 101);
  assert(strcmp(loaded_products[0].product_name, "Smartphone X") == 0);
  assert(strcmp(loaded_products[0].category, "Phone") == 0);
  assert(strcmp(loaded_products[0].brand, "Apple") == 0);
  assert(fabsf(loaded_products[0].price - 899.99F) < 0.001F);
  assert(loaded_products[0].stock_quantity == 45);

  assert(loaded_products[1].product_id == 102);
  assert(strcmp(loaded_products[1].product_name, "Laptop Y") == 0);
  assert(fabsf(loaded_products[1].price - 1299.50F) < 0.001F);
  assert(loaded_products[1].stock_quantity == 15);

  assert(loaded_bundle_count == 1);
  assert(loaded_bundles[0].bundle_id == 201);
  assert(strcmp(loaded_bundles[0].bundle_name, "Ultimate Bundle") == 0);
  assert(fabsf(loaded_bundles[0].discount_rate - 0.10F) < 0.001F);
  assert(fabsf(loaded_bundles[0].bundle_price - 1979.54F) < 0.001F);
  assert(loaded_bundles[0].product_count == 2);
  assert(loaded_bundles[0].product_ids[0] == 101);
  assert(loaded_bundles[0].product_ids[1] == 102);

  assert(loaded_order_count == 1);
  assert(loaded_orders[0].order_id == 301);
  assert(strcmp(loaded_orders[0].customer_name, "John Doe") == 0);
  assert(loaded_orders[0].item_id == 101);
  assert(loaded_orders[0].is_bundle == 0);
  assert(loaded_orders[0].quantity == 2);
  assert(fabsf(loaded_orders[0].total_price - 1799.98F) < 0.001F);
  assert(strcmp(loaded_orders[0].order_date, "2026-06-27") == 0);

  assert(loaded_admin.is_setup == 1);
  assert(strcmp(loaded_admin.username, "admin_user") == 0);
  assert(strcmp(loaded_admin.password, "securesaver123") == 0);

  printf("test_save_load_success passed!\n");
}

static void test_load_recovery_on_corruption(void) {
  printf("Running test_load_recovery_on_corruption...\n");
  clean_test_files();

  // 1. Setup initial active and backup files
  Product products[MAX_PRODUCTS];
  int product_count = 1;
  memset(products, 0, sizeof(products));
  products[0].product_id = 101;
  strcpy(products[0].product_name, "Smartphone X");
  strcpy(products[0].category, "Phone");
  strcpy(products[0].brand, "Apple");
  products[0].price = 899.99F;
  products[0].stock_quantity = 45;

  Bundle bundles[MAX_BUNDLES];
  int bundle_count = 0;
  Order orders[MAX_ORDERS];
  int order_count = 0;
  AdminCredentials admin;
  memset(&admin, 0, sizeof(admin));
  strcpy(admin.username, "admin_user");
  strcpy(admin.password, "securesaver123");
  admin.is_setup = 1;

  // Save normally (creates active products.txt and backup products.bak from a subsequent save, etc.)
  int save_res = save_database(products, product_count, bundles, bundle_count, orders, order_count, &admin);
  assert(save_res == 1);

  // Trigger a second save so that products.bak is created
  products[0].stock_quantity = 40;
  save_res = save_database(products, product_count, bundles, bundle_count, orders, order_count, &admin);
  assert(save_res == 1);

  // Verify backup exists
  FILE *fbak = fopen("products.bak", "r");
  assert(fbak != NULL);
  fclose(fbak);

  // 2. Corrupt active products.txt by making it empty
  FILE *fcorr = fopen("products.txt", "w");
  assert(fcorr != NULL);
  fclose(fcorr);

  // 3. Load database. It should trigger warning and restore from backup.
  Product loaded_products[MAX_PRODUCTS];
  int loaded_product_count = 0;
  Bundle loaded_bundles[MAX_BUNDLES];
  int loaded_bundle_count = 0;
  Order loaded_orders[MAX_ORDERS];
  int loaded_order_count = 0;
  AdminCredentials loaded_admin;
  memset(loaded_products, 0, sizeof(loaded_products));
  memset(loaded_bundles, 0, sizeof(loaded_bundles));
  memset(loaded_orders, 0, sizeof(loaded_orders));
  memset(&loaded_admin, 0, sizeof(loaded_admin));

  int load_res = load_database(loaded_products, &loaded_product_count,
                               loaded_bundles, &loaded_bundle_count,
                               loaded_orders, &loaded_order_count,
                               &loaded_admin);
  assert(load_res == 1);

  // 4. Verify data is recovered from the backup state (stock_quantity == 45)
  assert(loaded_product_count == 1);
  assert(loaded_products[0].product_id == 101);
  assert(loaded_products[0].stock_quantity == 45);

  // Check that products.txt is indeed restored and not empty now
  FILE *frestored = fopen("products.txt", "r");
  assert(frestored != NULL);
  fseek(frestored, 0, SEEK_END);
  long size = ftell(frestored);
  fclose(frestored);
  assert(size > 0);

  printf("test_load_recovery_on_corruption passed!\n");
}

int main(void) {
  test_save_load_success();
  test_load_recovery_on_corruption();
  clean_test_files();
  printf("All file_io tests completed successfully!\n");
  return 0;
}
