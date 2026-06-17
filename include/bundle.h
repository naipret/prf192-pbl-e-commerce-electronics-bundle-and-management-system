#ifndef BUNDLE_H
#define BUNDLE_H

#include "types.h"

int create_bundle(Bundle bundles[], int *count, const Bundle *new_bundle);
int add_product_to_bundle(Bundle *bundle, int product_id);
int remove_product_from_bundle(Bundle *bundle, int product_id);
float calculate_bundle_price(const Bundle *bundle, const Product products[],
                             int product_count);
int get_virtual_bundle_stock(const Bundle *bundle, const Product products[],
                             int product_count);
void display_all_bundles(const Bundle bundles[], int count,
                         const Product products[], int product_count);

#endif /* BUNDLE_H */
