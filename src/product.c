#include <stdio.h>
#include <string.h>

#include "product.h"

/**
 * @brief Helper function to validate product Category.
 * @param category The string to validate.
 * @return 1 if valid, 0 otherwise.
 */
static int is_valid_category(const char *category);

static int is_valid_category(const char *category) {
  if (category == NULL) {
    return 0;
  }
  return (strcmp(category, "Phone") == 0 || strcmp(category, "Laptop") == 0 ||
          strcmp(category, "Tablet") == 0 ||
          strcmp(category, "Accessory") == 0);
}

int add_product(Product products[], int *count, const Product *new_prod) {
  if (products == NULL || count == NULL || new_prod == NULL) {
    return 0;
  }
  if (*count >= MAX_PRODUCTS) {
    printf("Error: Maximum product limit reached (%d).\n", MAX_PRODUCTS);
    return 0;
  }
  if (new_prod->product_id <= 0) {
    printf("Error: Product ID must be a positive integer.\n");
    return 0;
  }
  // Check unique ID
  for (int i = 0; i < *count; i++) {
    if (products[i].product_id == new_prod->product_id) {
      printf("Error: Product ID %d already exists.\n", new_prod->product_id);
      return 0;
    }
  }
  // Validate Category
  if (!is_valid_category(new_prod->category)) {
    printf("Error: Invalid category '%s'. Category must strictly be one of: "
           "Phone, Laptop, Tablet, Accessory.\n",
           new_prod->category);
    return 0;
  }
  // Validate Price
  if (new_prod->price <= 0.0F) {
    printf("Error: Price must be a positive float value (> 0.0).\n");
    return 0;
  }
  // Validate Stock
  if (new_prod->stock_quantity < 0) {
    printf("Error: Stock quantity must be non-negative (>= 0).\n");
    return 0;
  }

  // Copy values safely
  products[*count].product_id = new_prod->product_id;

  strncpy(products[*count].product_name, new_prod->product_name,
          MAX_NAME_LEN - 1);
  products[*count].product_name[MAX_NAME_LEN - 1] = '\0';

  strncpy(products[*count].category, new_prod->category, MAX_CAT_LEN - 1);
  products[*count].category[MAX_CAT_LEN - 1] = '\0';

  strncpy(products[*count].brand, new_prod->brand, MAX_BRAND_LEN - 1);
  products[*count].brand[MAX_BRAND_LEN - 1] = '\0';

  products[*count].price = new_prod->price;
  products[*count].stock_quantity = new_prod->stock_quantity;

  (*count)++;
  return 1;
}

int update_product(Product products[], int count, int id,
                   const Product *updated) {
  if (products == NULL || updated == NULL || count < 0) {
    return 0;
  }
  int index = find_product_by_id(products, count, id);
  if (index == -1) {
    printf("Error: Product ID %d not found.\n", id);
    return 0;
  }
  // If ID is being changed, verify it is unique
  if (updated->product_id != id) {
    if (updated->product_id <= 0) {
      printf("Error: Product ID must be a positive integer.\n");
      return 0;
    }
    for (int i = 0; i < count; i++) {
      if (i != index && products[i].product_id == updated->product_id) {
        printf("Error: Product ID %d already exists.\n", updated->product_id);
        return 0;
      }
    }
  }
  // Validate Category
  if (!is_valid_category(updated->category)) {
    printf("Error: Invalid category '%s'. Category must strictly be one of: "
           "Phone, Laptop, Tablet, Accessory.\n",
           updated->category);
    return 0;
  }
  // Validate Price
  if (updated->price <= 0.0F) {
    printf("Error: Price must be a positive float value (> 0.0).\n");
    return 0;
  }
  // Validate Stock
  if (updated->stock_quantity < 0) {
    printf("Error: Stock quantity must be non-negative (>= 0).\n");
    return 0;
  }

  // Apply updates
  products[index].product_id = updated->product_id;

  strncpy(products[index].product_name, updated->product_name,
          MAX_NAME_LEN - 1);
  products[index].product_name[MAX_NAME_LEN - 1] = '\0';

  strncpy(products[index].category, updated->category, MAX_CAT_LEN - 1);
  products[index].category[MAX_CAT_LEN - 1] = '\0';

  strncpy(products[index].brand, updated->brand, MAX_BRAND_LEN - 1);
  products[index].brand[MAX_BRAND_LEN - 1] = '\0';

  products[index].price = updated->price;
  products[index].stock_quantity = updated->stock_quantity;

  return 1;
}

int delete_product(Product products[], int *count, int id,
                   const Bundle bundles[], int bundle_count) {
  if (products == NULL || count == NULL || bundles == NULL || *count < 0 ||
      bundle_count < 0) {
    return 0;
  }
  int index = find_product_by_id(products, *count, id);
  if (index == -1) {
    printf("Error: Product ID %d not found.\n", id);
    return 0;
  }

  // Check if the product is in any active bundle
  int is_blocked = 0;
  for (int i = 0; i < bundle_count; i++) {
    for (int j = 0; j < bundles[i].product_count; j++) {
      if (bundles[i].product_ids[j] == id) {
        if (!is_blocked) {
          printf("Cannot delete product. It is part of active bundles:\n");
          is_blocked = 1;
        }
        printf("- Bundle ID: %d, Name: %s\n", bundles[i].bundle_id,
               bundles[i].bundle_name);
        break; /* Check next bundle */
      }
    }
  }

  if (is_blocked) {
    return 0;
  }

  // Shift elements to the left
  for (int i = index; i < *count - 1; i++) {
    products[i] = products[i + 1];
  }
  (*count)--;
  return 1;
}

int find_product_by_id(const Product products[], int count, int id) {
  if (products == NULL || count < 0) {
    return -1;
  }
  for (int i = 0; i < count; i++) {
    if (products[i].product_id == id) {
      return i;
    }
  }
  return -1;
}

void display_all_products(const Product products[], int count) {
  if (products == NULL || count < 0) {
    return;
  }
  if (count == 0) {
    printf("No products currently in inventory.\n");
    return;
  }
  printf("%-6s | %-30s | %-12s | %-20s | %-10s | %-8s\n", "ID", "Name",
         "Category", "Brand", "Price", "Stock");
  printf("---------------------------------------------------------------------"
         "--------------------------------\n");
  for (int i = 0; i < count; i++) {
    printf("%-6d | %-30s | %-12s | %-20s | $%-9.2f | %-8d\n",
           products[i].product_id, products[i].product_name,
           products[i].category, products[i].brand, (double)products[i].price,
           products[i].stock_quantity);
  }
}
