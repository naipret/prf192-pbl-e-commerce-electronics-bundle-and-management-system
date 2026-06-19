#include <stdio.h>

#include "bundle.h"
#include "product.h"

int create_bundle(Bundle bundles[], const int *count,
                  const Bundle *new_bundle) {
  (void)bundles;
  (void)count;
  (void)new_bundle;
  return 0;
}

int add_product_to_bundle(Bundle *bundle, int product_id) {
  (void)bundle;
  (void)product_id;
  return 0;
}

int remove_product_from_bundle(Bundle *bundle, int product_id) {
  (void)bundle;
  (void)product_id;
  return 0;
}

float calculate_bundle_price(const Bundle *bundle, const Product products[],
                             int product_count) {
  if (bundle == NULL || products == NULL || product_count < 0) {
    return 0.0F;
  }
  float sum = 0.0F;
  for (int i = 0; i < bundle->product_count; i++) {
    int prod_id = bundle->product_ids[i];
    int prod_idx = find_product_by_id(products, product_count, prod_id);
    if (prod_idx != -1) {
      sum += products[prod_idx].price;
    }
  }
  return sum * (1.0F - bundle->discount_rate);
}

int get_virtual_bundle_stock(const Bundle *bundle, const Product products[],
                             int product_count) {
  if (bundle == NULL || products == NULL || product_count < 0) {
    return 0;
  }
  if (bundle->product_count <= 0) {
    return 0;
  }
  int min_stock = -1;
  for (int i = 0; i < bundle->product_count; i++) {
    int prod_id = bundle->product_ids[i];
    int prod_idx = find_product_by_id(products, product_count, prod_id);
    if (prod_idx == -1) {
      // If a product inside the bundle doesn't exist, we consider stock to be 0
      return 0;
    }
    int stock = products[prod_idx].stock_quantity;
    if (min_stock == -1 || stock < min_stock) {
      min_stock = stock;
    }
  }
  return (min_stock == -1) ? 0 : min_stock;
}

void display_all_bundles(const Bundle bundles[], int count,
                         const Product products[], int product_count) {
  (void)bundles;
  (void)count;
  (void)products;
  (void)product_count;
}
