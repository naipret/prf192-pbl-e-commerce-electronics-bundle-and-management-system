#include <stdio.h>

#include "order.h"

int create_order(Order orders[], int *count, Product products[],
                 int product_count, const Bundle bundles[], int bundle_count,
                 const Order *new_order) {
  (void)orders;
  (void)count;
  (void)products;
  (void)product_count;
  (void)bundles;
  (void)bundle_count;
  (void)new_order;
  return 0;
}

void display_order_history(const Order orders[], int count) {
  (void)orders;
  (void)count;
}

void print_revenue_report(const Order orders[], int order_count,
                          const Product products[], int product_count,
                          const Bundle bundles[], int bundle_count) {
  (void)orders;
  (void)order_count;
  (void)products;
  (void)product_count;
  (void)bundles;
  (void)bundle_count;
}
