#include <stdio.h>
#include <string.h>
#include <time.h>

#include "bundle.h"
#include "order.h"
#include "product.h"
#include "utils.h"

/* Static helper function prototypes */
static int process_product_order(Product products[], int product_count,
                                 const Order *new_order, float *item_price);
static int process_bundle_order(Product products[], int product_count,
                                const Bundle bundles[], int bundle_count,
                                const Order *new_order, float *item_price);
static void finalize_order_metadata(Order *ord, const Order *orders, int count,
                                    const Order *new_order, float item_price);

/**
 * @brief Processes and validates a product-based order.
 */
static int process_product_order(Product products[], int product_count,
                                 const Order *new_order, float *item_price) {
  int prod_idx =
      find_product_by_id(products, product_count, new_order->item_id);
  if (prod_idx == -1) {
    printf("Error: Product ID %d does not exist.\n", new_order->item_id);
    return 0;
  }
  Product *prod = &products[prod_idx];
  if (prod->stock_quantity < new_order->quantity) {
    printf("Error: Insufficient stock available.\n");
    return 0;
  }
  prod->stock_quantity -= new_order->quantity;
  *item_price = prod->price;
  return 1;
}

/**
 * @brief Processes and validates a bundle-based order.
 */
static int process_bundle_order(Product products[], int product_count,
                                const Bundle bundles[], int bundle_count,
                                const Order *new_order, float *item_price) {
  int bundle_idx = -1;
  for (int i = 0; i < bundle_count; i++) {
    if (bundles[i].bundle_id == new_order->item_id) {
      bundle_idx = i;
      break;
    }
  }
  if (bundle_idx == -1) {
    printf("Error: Bundle ID %d does not exist.\n", new_order->item_id);
    return 0;
  }
  const Bundle *bundle = &bundles[bundle_idx];
  int virtual_stock = get_virtual_bundle_stock(bundle, products, product_count);
  if (virtual_stock < new_order->quantity) {
    printf("Error: Insufficient stock available.\n");
    for (int i = 0; i < bundle->product_count; i++) {
      int prod_id = bundle->product_ids[i];
      int prod_idx = find_product_by_id(products, product_count, prod_id);
      if (prod_idx != -1) {
        int stock = products[prod_idx].stock_quantity;
        if (stock < new_order->quantity) {
          printf("  - Product '%s' (ID %d) has insufficient stock. Requested: "
                 "%d, Available: %d.\n",
                 products[prod_idx].product_name, prod_id, new_order->quantity,
                 stock);
        }
      } else {
        printf("  - Product ID %d in bundle does not exist.\n", prod_id);
      }
    }
    return 0;
  }
  for (int i = 0; i < bundle->product_count; i++) {
    int prod_id = bundle->product_ids[i];
    int prod_idx = find_product_by_id(products, product_count, prod_id);
    if (prod_idx != -1) {
      products[prod_idx].stock_quantity -= new_order->quantity;
    }
  }
  *item_price = calculate_bundle_price(bundle, products, product_count);
  return 1;
}

/**
 * @brief Populates metadata for the newly placed order.
 */
static void finalize_order_metadata(Order *ord, const Order *orders, int count,
                                    const Order *new_order, float item_price) {
  ord->order_id = new_order->order_id;
  if (ord->order_id <= 0) {
    int max_id = 0;
    for (int i = 0; i < count; i++) {
      if (orders[i].order_id > max_id) {
        max_id = orders[i].order_id;
      }
    }
    ord->order_id = max_id + 1;
  }
  strncpy(ord->customer_name, new_order->customer_name,
          sizeof(ord->customer_name) - 1);
  ord->customer_name[sizeof(ord->customer_name) - 1] = '\0';
  ord->item_id = new_order->item_id;
  ord->is_bundle = new_order->is_bundle;
  ord->quantity = new_order->quantity;
  ord->total_price = item_price * (float)new_order->quantity;

  if (strlen(new_order->order_date) > 0) {
    strncpy(ord->order_date, new_order->order_date,
            sizeof(ord->order_date) - 1);
    ord->order_date[sizeof(ord->order_date) - 1] = '\0';
  } else {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    if (tm_info != NULL) {
      strftime(ord->order_date, sizeof(ord->order_date), "%Y-%m-%d", tm_info);
    } else {
      strncpy(ord->order_date, "2026-06-19", sizeof(ord->order_date) - 1);
      ord->order_date[sizeof(ord->order_date) - 1] = '\0';
    }
  }
}

int create_order(Order orders[], int *count, Product products[],
                 int product_count, const Bundle bundles[], int bundle_count,
                 const Order *new_order) {
  if (orders == NULL || count == NULL || products == NULL || bundles == NULL ||
      new_order == NULL) {
    return 0;
  }
  if (*count < 0 || *count >= MAX_ORDERS) {
    printf("Error: Order limit reached or invalid count.\n");
    return 0;
  }

  // 1. Validate quantity
  if (new_order->quantity <= 0) {
    printf("Error: Order quantity must be greater than 0.\n");
    return 0;
  }

  // 2. Validate customer name
  if (strlen(new_order->customer_name) == 0) {
    printf("Error: Customer name cannot be empty.\n");
    return 0;
  }

  float item_price = 0.0F;

  // 3. Process Product/Bundle Order
  if (new_order->is_bundle == 0) {
    if (!process_product_order(products, product_count, new_order,
                               &item_price)) {
      return 0;
    }
  } else if (new_order->is_bundle == 1) {
    if (!process_bundle_order(products, product_count, bundles, bundle_count,
                              new_order, &item_price)) {
      return 0;
    }
  } else {
    printf("Error: Invalid item type flag (is_bundle must be 0 or 1).\n");
    return 0;
  }

  // 4. Finalize Metadata and append
  finalize_order_metadata(&orders[*count], orders, *count, new_order,
                          item_price);
  (*count)++;
  return 1;
}

void display_order_history(const Order orders[], int count) {
  if (orders == NULL || count <= 0) {
    printf("\nNo orders found in history.\n");
    return;
  }
  printf("\n=================================== ORDER HISTORY "
         "===================================\n");
  printf("%-8s | %-20s | %-8s | %-10s | %-8s | %-12s | %-10s\n", "Order ID",
         "Customer Name", "Item ID", "Item Type", "Quantity", "Total Price",
         "Date");
  printf("---------------------------------------------------------------------"
         "----------------\n");
  for (int i = 0; i < count; i++) {
    printf("%-8d | %-20s | %-8d | %-10s | %-8d | $%-11.2f | %-10s\n",
           orders[i].order_id, orders[i].customer_name, orders[i].item_id,
           orders[i].is_bundle ? "Bundle" : "Product", orders[i].quantity,
           (double)orders[i].total_price, orders[i].order_date);
  }
  printf("====================================================================="
         "===========-----\n");
}

void print_revenue_report(const Order orders[], int order_count,
                          const Product products[], int product_count,
                          const Bundle bundles[], int bundle_count) {
  int product_sold = 0;
  int bundle_sold = 0;
  float total_revenue = 0.0F;

  (void)products;
  (void)product_count;
  (void)bundles;
  (void)bundle_count;

  if (orders == NULL || order_count <= 0) {
    printf("\n--- REVENUE REPORT ---\n");
    printf("Total Orders: 0\n");
    printf("Total Revenue: $0.00\n");
    return;
  }

  for (int i = 0; i < order_count; i++) {
    if (orders[i].is_bundle == 0) {
      product_sold += orders[i].quantity;
    } else {
      bundle_sold += orders[i].quantity;
    }
    total_revenue += orders[i].total_price;
  }

  printf("\n--- REVENUE REPORT ---\n");
  printf("Total Orders: %d\n", order_count);
  printf("Total Revenue: $%.2f\n", (double)total_revenue);
  printf("Total count of products sold: %d\n", product_sold);
  printf("Total count of bundles sold: %d\n", bundle_sold);
}

void print_best_seller_products(const Order orders[], int order_count,
                                const Product products[], int product_count,
                                const Bundle bundles[], int bundle_count) {
  int product_sales[MAX_PRODUCTS] = {0};
  int best_seller = 0;
  int stt = 1;

  if (orders == NULL || order_count <= 0 || products == NULL ||
      product_count <= 0) {
    printf("No products or bundles have been sold yet.\n");
    cont();
    return;
  }

  for (int i = 0; i < product_count; i++) {
    int prod_id = products[i].product_id;
    int total = 0;
    for (int j = 0; j < order_count; j++) {
      if (orders[j].is_bundle == 0) {
        if (orders[j].item_id == prod_id) {
          total += orders[j].quantity;
        }
      } else {
        int b_idx = find_bundle_by_id(bundles, bundle_count, orders[j].item_id);
        if (b_idx != -1) {
          for (int k = 0; k < bundles[b_idx].product_count; k++) {
            if (bundles[b_idx].product_ids[k] == prod_id) {
              total += orders[j].quantity;
              break;
            }
          }
        }
      }
    }
    product_sales[i] = total;
    if (total > best_seller) {
      best_seller = total;
    }
  }

  if (best_seller == 0) {
    printf("No products have been sold yet.\n");
    cont();
    return;
  }

  printf("\n+-----+-----------------------------------+------------+\n");
  printf("| %-3s | %-33s | %-10s |\n", "No", "Product Name", "Total Sold");
  printf("+-----+-----------------------------------+------------+\n");

  for (int i = 0; i < product_count; i++) {
    if (product_sales[i] == best_seller) {
      printf("| %-3d | %-33s | %-10d |\n", stt, products[i].product_name,
             best_seller);
      stt++;
    }
  }
  printf("+-----+-----------------------------------+------------+\n");

  cont();
}

void print_best_seller_bundles(const Order orders[], int order_count,
                               const Bundle bundles[], int bundle_count) {
  int bundle_sales[MAX_BUNDLES] = {0};
  int best_seller = 0;
  int stt = 1;

  if (orders == NULL || order_count <= 0 || bundles == NULL ||
      bundle_count <= 0) {
    printf("No bundles have been sold yet.\n");
    cont();
    return;
  }

  for (int i = 0; i < bundle_count; i++) {
    int b_id = bundles[i].bundle_id;
    int total = 0;
    for (int j = 0; j < order_count; j++) {
      if (orders[j].is_bundle == 1 && orders[j].item_id == b_id) {
        total += orders[j].quantity;
      }
    }
    bundle_sales[i] = total;
    if (total > best_seller) {
      best_seller = total;
    }
  }

  if (best_seller == 0) {
    printf("No bundles have been sold yet.\n");
    cont();
    return;
  }

  printf("\n+-----+-----------------------------------+------------+\n");
  printf("| %-3s | %-33s | %-10s |\n", "No", "Bundle Name", "Total Sold");
  printf("+-----+-----------------------------------+------------+\n");
  for (int i = 0; i < bundle_count; i++) {
    if (bundle_sales[i] == best_seller) {
      printf("| %-3d | %-33s | %-10d |\n", stt, bundles[i].bundle_name,
             best_seller);
      stt++;
    }
  }
  printf("+-----+-----------------------------------+------------+\n");

  cont();
}

void alert_low_stock(const Product products[], int product_count) {
  int check = 1;
  int stt = 1;
  const char *border = "+------+--------+--------------------------------------"
                       "--------------+--------------+";

  printf("%s\n", border);
  printf("| %-4s | %-6s | %-50s | %-12s |\n", "NO", "ID", "NAME",
         "CURRENT STOCK");
  printf("%s\n", border);

  for (int i = 0; i < product_count; i++) {
    if (products[i].stock_quantity < 5) {
      check = 0;

      printf("| %-4d | %-6d | %-50.50s | %-12d |\n", stt,
             products[i].product_id, products[i].product_name,
             products[i].stock_quantity);
      stt++;
    }
  }

  if (!check) {
    printf("%s\n", border);
  } else {
    printf("\nAll products have sufficient stock levels.\n");
  }

  cont();
}