#include <stdio.h>

#include "product.h"

int add_product(Product products[], int *count, const Product *new_prod) {
  (void)products;
  (void)count;
  (void)new_prod;
  return 0;
}

int update_product(Product products[], int count, int id,
                   const Product *updated) {
  (void)products;
  (void)count;
  (void)id;
  (void)updated;
  return 0;
}

int delete_product(Product products[], int *count, int id,
                   const int active_bundle_prod_ids[],
                   int active_bundle_count) {
  (void)products;
  (void)count;
  (void)id;
  (void)active_bundle_prod_ids;
  (void)active_bundle_count;
  return 0;
}

int find_product_by_id(const Product products[], int count, int id) {
  (void)products;
  (void)count;
  (void)id;
  return -1;
}

void display_all_products(const Product products[], int count) {
  (void)products;
  (void)count;
}
