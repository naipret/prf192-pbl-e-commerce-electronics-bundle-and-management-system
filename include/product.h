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

/**
 * @brief Searches for products by name (case-insensitive substring match).
 * @param products Array of product structures.
 * @param count Current number of active products.
 * @param query The string to search for.
 */
void search_product_by_name(const Product products[], int count,
                            const char *query);

/**
 * @brief Filters products by category (matching strictly one of "Phone",
 * "Laptop", "Tablet", "Accessory").
 * @param products Array of product structures.
 * @param count Current number of active products.
 * @param category The category string to match.
 */
void filter_product_by_category(const Product products[], int count,
                                const char *category);

/**
 * @brief Filters products by price range (MinPrice <= price <= MaxPrice).
 * @param products Array of product structures.
 * @param count Current number of active products.
 * @param min_price Minimum price boundary.
 * @param max_price Maximum price boundary.
 */
void filter_product_by_price(const Product products[], int count,
                             float min_price, float max_price);

#endif /* PRODUCT_H */
