#ifndef BUNDLE_H
#define BUNDLE_H

#include "types.h"

/**
 * @brief Creates a new bundle and appends it to the bundles array if valid.
 * @param bundles Array of current bundles in the system.
 * @param count Pointer to the number of bundles. Incremented on success.
 * @param new_bundle Pointer to the new bundle structure to create.
 * @return 1 on success, 0 on failure (e.g. limit reached, invalid discount, empty product list).
 */
int create_bundle(Bundle bundles[], int *count, const Bundle *new_bundle);

/**
 * @brief Adds a product ID to an existing bundle.
 * @param bundle Pointer to the bundle structure to modify.
 * @param product_id The ID of the product to add.
 * @return 1 on success, 0 on failure (e.g. bundle full, product already exists in bundle).
 */
int add_product_to_bundle(Bundle *bundle, int product_id);

/**
 * @brief Removes a product from a bundle, shifting remaining items.
 * @details If removing the product results in an empty bundle (product_count drops to 0),
 *          the bundle is deleted from the array.
 *          Note: Deleting the bundle from the array shifts elements and invalidates the bundle pointer.
 * @param bundles Array of current bundles in the system.
 * @param bundle_count Pointer to the current count of bundles. Decremented if bundle is deleted.
 * @param bundle Pointer to the bundle structure to modify.
 * @param product_id The ID of the product to remove.
 * @return 1 if product was successfully removed (or bundle deleted), 0 on failure (e.g. product not in bundle).
 */
int remove_product_from_bundle(Bundle bundles[], int *bundle_count,
                               Bundle *bundle, int product_id);

/**
 * @brief Calculates the total price of a bundle after applying its discount.
 * @param bundle Pointer to the bundle to calculate.
 * @param products Array of all products in inventory for lookup.
 * @param product_count Current number of active products.
 * @return The calculated discounted bundle price.
 */
float calculate_bundle_price(const Bundle *bundle, const Product products[],
                             int product_count);

/**
 * @brief Calculates the virtual stock of a bundle based on the minimum stock of its products.
 * @param bundle Pointer to the bundle to query.
 * @param products Array of all products in inventory for lookup.
 * @param product_count Current number of active products.
 * @return The virtual stock of the bundle, or 0 if missing any product or if the bundle is empty.
 */
int get_virtual_bundle_stock(const Bundle *bundle, const Product products[],
                             int product_count);

/**
 * @brief Prints details of all bundles in the catalog in a formatted table.
 * @param bundles Array of bundles.
 * @param count Current number of active bundles.
 * @param products Array of all products in inventory.
 * @param product_count Current number of active products.
 */
void display_all_bundles(const Bundle bundles[], int count,
                         const Product products[], int product_count);

#endif /* BUNDLE_H */

