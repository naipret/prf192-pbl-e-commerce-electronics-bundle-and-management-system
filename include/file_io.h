#ifndef FILE_IO_H
#define FILE_IO_H

#include "admin.h"
#include "bundle.h"
#include "order.h"
#include "product.h"

/**
 * @brief Saves the database containing products, bundles, orders, and admin
 * credentials.
 * @param products Array of current products.
 * @param product_count Number of active products.
 * @param bundles Array of current bundles.
 * @param bundle_count Number of active bundles.
 * @param orders Array of current orders.
 * @param order_count Number of active orders.
 * @param admin Pointer to the admin credentials.
 * @return 1 on success, 0 on failure.
 */
int save_database(const Product products[], int product_count,
                  const Bundle bundles[], int bundle_count,
                  const Order orders[], int order_count,
                  const AdminCredentials *admin);

/**
 * @brief Loads the database containing products, bundles, orders, and admin
 * credentials.
 * @param products Array to populate with products.
 * @param product_count Pointer to variable storing loaded products count.
 * @param bundles Array to populate with bundles.
 * @param bundle_count Pointer to variable storing loaded bundles count.
 * @param orders Array to populate with orders.
 * @param order_count Pointer to variable storing loaded orders count.
 * @param admin Pointer to the admin credentials structure to populate.
 * @return 1 on success, 0 on failure.
 */
int load_database(Product products[], int *product_count, Bundle bundles[],
                  int *bundle_count, Order orders[], int *order_count,
                  AdminCredentials *admin);

#endif /* FILE_IO_H */
