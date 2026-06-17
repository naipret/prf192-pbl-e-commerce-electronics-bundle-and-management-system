#ifndef FILE_IO_H
#define FILE_IO_H

#include "admin.h"
#include "bundle.h"
#include "order.h"
#include "product.h"

int save_database(const Product products[], int product_count,
                  const Bundle bundles[], int bundle_count,
                  const Order orders[], int order_count,
                  const AdminCredentials *admin);
int load_database(Product products[], int *product_count, Bundle bundles[],
                  int *bundle_count, Order orders[], int *order_count,
                  AdminCredentials *admin);

#endif /* FILE_IO_H */
