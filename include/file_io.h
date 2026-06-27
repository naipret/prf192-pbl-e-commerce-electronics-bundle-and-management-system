#ifndef FILE_IO_H
#define FILE_IO_H

#include "admin.h"
#include "bundle.h"
#include "order.h"
#include "product.h"

/**
 * @brief Saves products, bundles, orders, and admin credentials safely using a
 * transactional swap (.tmp -> .bak -> .txt).
 * @param products Array of product records.
 * @param product_count Current number of product records.
 * @param bundles Array of bundle records.
 * @param bundle_count Current number of bundle records.
 * @param orders Array of order records.
 * @param order_count Current number of order records.
 * @param admin Pointer to admin credentials structure.
 * @return 1 if all saves succeed, 0 otherwise.
 */
int save_database(const Product products[], int product_count,
                  const Bundle bundles[], int bundle_count,
                  const Order orders[], int order_count,
                  const AdminCredentials *admin);

/**
 * @brief Loads products, bundles, orders, and admin credentials from the active
 * database files. If an active file is missing or empty, attempts to restore it
 * from the .bak backup file.
 * @param products Destination array for product records.
 * @param product_count Pointer to update with the loaded product count.
 * @param bundles Destination array for bundle records.
 * @param bundle_count Pointer to update with the loaded bundle count.
 * @param orders Destination array for order records.
 * @param order_count Pointer to update with the loaded order count.
 * @param admin Pointer to update with loaded admin credentials.
 * @return 1 if databases are successfully loaded/restored, 0 otherwise.
 */
int load_database(Product products[], int *product_count, Bundle bundles[],
                  int *bundle_count, Order orders[], int *order_count,
                  AdminCredentials *admin);

#endif /* FILE_IO_H */
