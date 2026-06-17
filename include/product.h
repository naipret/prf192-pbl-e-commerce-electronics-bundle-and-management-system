#ifndef PRODUCT_H
#define PRODUCT_H

#include "types.h"

int add_product(Product products[], int *count, const Product *new_prod);
int update_product(Product products[], int count, int id,
                   const Product *updated);
int delete_product(Product products[], int *count, int id,
                   const int active_bundle_prod_ids[], int active_bundle_count);
int find_product_by_id(const Product products[], int count, int id);
void display_all_products(const Product products[], int count);

#endif /* PRODUCT_H */
