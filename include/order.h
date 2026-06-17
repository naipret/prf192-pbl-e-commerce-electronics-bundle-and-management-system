#ifndef ORDER_H
#define ORDER_H

#include "types.h"

int create_order(Order orders[], int *count, Product products[],
                 int product_count, const Bundle bundles[], int bundle_count,
                 const Order *new_order);
void display_order_history(const Order orders[], int count);
void print_revenue_report(const Order orders[], int order_count,
                          const Product products[], int product_count,
                          const Bundle bundles[], int bundle_count);

#endif /* ORDER_H */
