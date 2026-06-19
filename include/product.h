#ifndef PRODUCT_H
#define PRODUCT_H

#include "types.h"

/**
 * @brief Adds a new product to the inventory array after validation.
 * @param products Array of product structures.
 * @param count Pointer to the current count of products. Incremented on
 * success.
 * @param new_prod Pointer to the new product structure to be added.
 * @return 1 if product added successfully, 0 if validation fails or limit
 * reached.
 */
int add_product(Product products[], int *count, const Product *new_prod);

/**
 * @brief Updates an existing product's details in the inventory array.
 * @param products Array of product structures.
 * @param count Current number of active products.
 * @param id The ID of the product to update.
 * @param updated Pointer to the product structure containing the updated
 * details.
 * @return 1 if updated successfully, 0 if product ID not found or validation
 * fails.
 */
int update_product(Product products[], int count, int id,
                   const Product *updated);

/**
 * @brief Removes a product from the inventory array, shifting remaining items.
 * @param products Array of product structures.
 * @param count Pointer to the current count of products. Decremented on
 * success.
 * @param id The ID of the product to delete.
 * @param bundles Array of current bundles to check active association.
 * @param bundle_count Current number of bundles.
 * @return 1 if deleted successfully, 0 if product ID not found or deletion is
 * blocked.
 */
int delete_product(Product products[], int *count, int id,
                   const Bundle bundles[], int bundle_count);

/**
 * @brief Searches for a product in the inventory array by its unique ID.
 * @param products Array of product structures.
 * @param count Current number of active products.
 * @param id The ID of the product to search for.
 * @return The array index of the matching product, or -1 if not found.
 */
int find_product_by_id(const Product products[], int count, int id);

/**
 * @brief Displays all products in the inventory array in a clean format.
 * @param products Array of product structures.
 * @param count Current number of active products.
 */
void display_all_products(const Product products[], int count);

#endif /* PRODUCT_H */
