#include <stdio.h>
#include <string.h>

#include "bundle.h"
#include "product.h"
#include "utils.h"

int create_bundle(Bundle bundles[], int *count, const Bundle *new_bundle) {
  if (bundles == NULL || count == NULL || new_bundle == NULL) {
    return 0;
  }
  if (*count >= MAX_BUNDLES) {
    printf("Error: Maximum bundle limit reached (%d).\n", MAX_BUNDLES);
    cont();
    return 0;
  }
  if (new_bundle->discount_rate < 0.0F || new_bundle->discount_rate > 1.0F) {
    printf("Discount rate must be between 0.0 and 1.0.\n");
    cont();
    return 0;
  }
  if (new_bundle->product_count < 1) {
    printf("Error: A bundle must contain at least 1 product.\n");
    cont();
    return 0;
  }
  if (new_bundle->product_count > MAX_BUNDLE_ITEMS) {
    printf("Error: A bundle can only contain up to %d products.\n",
           MAX_BUNDLE_ITEMS);
    cont();
    return 0;
  }
  // Verify unique product IDs in the new bundle
  for (int i = 0; i < new_bundle->product_count; i++) {
    for (int j = i + 1; j < new_bundle->product_count; j++) {
      if (new_bundle->product_ids[i] == new_bundle->product_ids[j]) {
        printf("Error: Duplicate product ID %d in bundle.\n",
               new_bundle->product_ids[i]);
        cont();
        return 0;
      }
    }
  }

  bundles[*count] = *new_bundle;
  (*count)++;
  return 1;
}

int add_product_to_bundle(Bundle *bundle, int product_id) {
  if (bundle == NULL) {
    return 0;
  }
  if (bundle->product_count >= MAX_BUNDLE_ITEMS) {
    printf("Maximum limit reached: You can only add up to %d products to a "
           "bundle.\n",
           MAX_BUNDLE_ITEMS);
    cont();
    return 0;
  }
  for (int i = 0; i < bundle->product_count; i++) {
    if (bundle->product_ids[i] == product_id) {
      printf("This product is already in the bundle.\n");
      cont();
      return 0;
    }
  }
  bundle->product_ids[bundle->product_count] = product_id;
  bundle->product_count++;
  return 1;
}

int remove_product_from_bundle(Bundle bundles[], int *bundle_count,
                               Bundle *bundle, int product_id) {
  if (bundles == NULL || bundle_count == NULL || bundle == NULL) {
    return 0;
  }
  int cnt = bundle->product_count;
  int index = -1;
  for (int i = 0; i < cnt; i++) {
    if (bundle->product_ids[i] == product_id) {
      index = i;
      break;
    }
  }
  if (index == -1) {
    printf("The bundle does not contain this product.\n");
    cont();
    return 0;
  }
  if (cnt == 1) {
    if (confirm_action(
            "This action will also delete the bundle. Do you want to "
            "continue?")) {
      int delete_idx = -1;
      for (int i = 0; i < *bundle_count; i++) {
        if (bundles[i].bundle_id == bundle->bundle_id) {
          delete_idx = i;
          break;
        }
      }
      if (delete_idx != -1) {
        for (int i = delete_idx; i < *bundle_count - 1; i++) {
          bundles[i] = bundles[i + 1];
        }
        (*bundle_count)--;
        return 1;
      }
    }
    return 0;
  }
  // Standard removal and shift
  for (int i = index; i < cnt - 1; i++) {
    bundle->product_ids[i] = bundle->product_ids[i + 1];
  }
  bundle->product_count--;
  return 1;
}
float calculate_bundle_price(const Bundle *bundle, const Product products[],
                             int product_count) {
  if (bundle == NULL || products == NULL || product_count < 0) {
    return 0.0F;
  }
  float sum = 0.0F;
  for (int i = 0; i < bundle->product_count; i++) {
    int prod_id = bundle->product_ids[i];
    int prod_idx = find_product_by_id(products, product_count, prod_id);
    if (prod_idx != -1) {
      sum += products[prod_idx].price;
    }
  }
  return sum * (1.0F - bundle->discount_rate);
}

int get_virtual_bundle_stock(const Bundle *bundle, const Product products[],
                             int product_count) {
  if (bundle == NULL || products == NULL || product_count < 0) {
    return 0;
  }
  if (bundle->product_count <= 0) {
    return 0;
  }
  int min_stock = -1;
  for (int i = 0; i < bundle->product_count; i++) {
    int prod_id = bundle->product_ids[i];
    int prod_idx = find_product_by_id(products, product_count, prod_id);
    if (prod_idx == -1) {
      // If a product inside the bundle doesn't exist, we consider stock to be 0
      return 0;
    }
    int stock = products[prod_idx].stock_quantity;
    if (min_stock == -1 || stock < min_stock) {
      min_stock = stock;
    }
  }
  return (min_stock == -1) ? 0 : min_stock;
}

void display_all_bundles(const Bundle bundles[], int count,
                         const Product products[], int product_count) {
  if (bundles == NULL || products == NULL || count < 0 || product_count < 0) {
    return;
  }
  if (count == 0) {
    printf("\nNo bundles available in the system.\n");
    cont();
    return;
  }
  // +----+---------------------------+-------------+---------------+---------------+
  char border[] = "+----+---------------------------+-------------+------------"
                  "---+---------------+";

  printf("\n%s\n", border);
  printf("| %-2s | %-25s | %-11s | %-13s | %-13s |\n", "ID", "Bundle Name",
         "Disc. Rate", "Price (Final)", "Virt. Stock");
  printf("%s\n", border);

  for (int i = 0; i < count; i++) {
    float final_price =
        calculate_bundle_price(&bundles[i], products, product_count);
    int virtual_stock =
        get_virtual_bundle_stock(&bundles[i], products, product_count);

    float discount_percentage = bundles[i].discount_rate * 100.0F;

    printf("| %-2d | %-25s | %-10.1f%% | %-13.2f | %-13d |\n",
           bundles[i].bundle_id, bundles[i].bundle_name,
           (double)discount_percentage, (double)final_price, virtual_stock);
  }

  printf("%s\n", border);
  cont();
}