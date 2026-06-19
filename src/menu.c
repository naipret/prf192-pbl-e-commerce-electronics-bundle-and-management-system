#include <stdio.h>
#include <string.h>

#include "admin.h"
#include "bundle.h"
#include "file_io.h"
#include "menu.h"
#include "order.h"
#include "product.h"
#include "utils.h"

static Product products[MAX_PRODUCTS];
static int product_count = 0;
static Bundle bundles[MAX_BUNDLES];
static int bundle_count = 0;
static Order orders[MAX_ORDERS];
static int order_count = 0;
static AdminCredentials admin;

void display_customer_menu(void) {
  int choice = -1;
  while (1) {
    printf("\n==========================================\n");
    printf("              CUSTOMER MENU               \n");
    printf("==========================================\n");
    printf("1. Browse Catalog\n");
    printf("2. Search/Sort Products\n");
    printf("3. Place Order\n");
    printf("4. Switch to Admin Mode\n");
    printf("0. Exit\n");
    printf("------------------------------------------\n");

    if (get_safe_int("Enter selection: ", &choice) == 0) {
      printf("Goodbye!\n");
      break;
    }

    if (choice == 0) {
      printf("Goodbye!\n");
      break;
    }

    switch (choice) {
    case 1:
      printf("\n--- Product Catalog ---\n");
      display_all_products(products, product_count);
      break;
    case 2:
      printf("Search/Sort function is not implemented yet.\n");
      break;
    case 3:
      printf("Order placement function is not implemented yet.\n");
      break;
    case 4: {
      printf("\n--- Admin Login ---\n");
      char username[MAX_USERNAME_LEN] = {0};
      char password[MAX_PASSWORD_LEN] = {0};
      int login_success = 0;
      int attempts = 0;
      while (attempts < 3) {
        get_safe_string("Enter Username (0 to cancel): ", username,
                        MAX_USERNAME_LEN);
        if (strcmp(username, "0") == 0) {
          break;
        }
        get_safe_string("Enter Password (0 to cancel): ", password,
                        MAX_PASSWORD_LEN);
        if (strcmp(password, "0") == 0) {
          break;
        }

        if (verify_admin_login(username, password) != 0) {
          printf("Login successful!\n");
          login_success = 1;
          break;
        }

        attempts++;
        printf("Invalid credentials. Attempt %d/3 failed.\n", attempts);
      }

      if (attempts >= 3) {
        printf("Too many failed attempts. Entry to Admin Mode locked for this "
               "session.\n");
      } else if (login_success != 0) {
        display_admin_menu();
      }
      break;
    }
    default:
      printf("Invalid option. Please try again.\n");
      break;
    }
  }
}

void display_admin_menu(void) {
  int choice = -1;
  while (1) {
    printf("\n==========================================\n");
    printf("               ADMIN MENU                 \n");
    printf("==========================================\n");
    printf("1. Manage Products\n");
    printf("2. Manage Bundles\n");
    printf("3. View Revenue & Reports\n");
    printf("4. Save Changes\n");
    printf("0. Logout\n");
    printf("------------------------------------------\n");

    if (get_safe_int("Enter selection: ", &choice) == 0) {
      printf("Logging out of admin mode...\n");
      break;
    }

    if (choice == 0) {
      printf("Logging out of admin mode...\n");
      break;
    }

    switch (choice) {
    case 1: {
      int prod_choice = -1;
      while (1) {
        printf("\n--- Product Management Sub-Menu ---\n");
        printf("1. View All Products\n");
        printf("2. Add Product\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("0. Back\n");
        printf("-----------------------------------\n");

        if (get_safe_int("Enter selection: ", &prod_choice) == 0 ||
            prod_choice == 0) {
          break;
        }

        switch (prod_choice) {
        case 1:
          display_all_products(products, product_count);
          break;
        case 2: {
          printf("\n--- Add Product ---\n");
          Product new_prod;
          memset(&new_prod, 0, sizeof(new_prod));

          if (get_safe_int("Enter Product ID (0 to cancel): ",
                           &new_prod.product_id) == 0) {
            printf("Action cancelled.\n");
            break;
          }

          get_safe_string("Enter Product Name (0 to cancel): ",
                          new_prod.product_name, MAX_NAME_LEN);
          if (strcmp(new_prod.product_name, "0") == 0) {
            printf("Action cancelled.\n");
            break;
          }

          get_safe_string(
              "Enter Category (Phone/Laptop/Tablet/Accessory, 0 to cancel): ",
              new_prod.category, MAX_CAT_LEN);
          if (strcmp(new_prod.category, "0") == 0) {
            printf("Action cancelled.\n");
            break;
          }

          get_safe_string("Enter Brand (0 to cancel): ", new_prod.brand,
                          MAX_BRAND_LEN);
          if (strcmp(new_prod.brand, "0") == 0) {
            printf("Action cancelled.\n");
            break;
          }

          if (get_safe_float("Enter Price (0 to cancel): ", &new_prod.price) ==
              0) {
            printf("Action cancelled.\n");
            break;
          }

          if (get_safe_int("Enter Stock Quantity (0 to cancel): ",
                           &new_prod.stock_quantity) == 0) {
            printf("Action cancelled.\n");
            break;
          }

          if (add_product(products, &product_count, &new_prod) != 0) {
            printf("Product added successfully!\n");
          } else {
            printf("Failed to add product due to validation errors.\n");
          }
          break;
        }
        case 3: {
          printf("\n--- Update Product ---\n");
          int update_id = 0;
          if (get_safe_int("Enter Product ID to Update (0 to cancel): ",
                           &update_id) == 0) {
            printf("Action cancelled.\n");
            break;
          }

          int index = find_product_by_id(products, product_count, update_id);
          if (index == -1) {
            printf("Error: Product ID %d not found.\n", update_id);
            break;
          }

          Product updated;
          memset(&updated, 0, sizeof(updated));

          if (get_safe_int("Enter New Product ID (0 to cancel): ",
                           &updated.product_id) == 0) {
            printf("Action cancelled.\n");
            break;
          }

          get_safe_string("Enter New Product Name (0 to cancel): ",
                          updated.product_name, MAX_NAME_LEN);
          if (strcmp(updated.product_name, "0") == 0) {
            printf("Action cancelled.\n");
            break;
          }

          get_safe_string("Enter New Category (Phone/Laptop/Tablet/Accessory, "
                          "0 to cancel): ",
                          updated.category, MAX_CAT_LEN);
          if (strcmp(updated.category, "0") == 0) {
            printf("Action cancelled.\n");
            break;
          }

          get_safe_string("Enter New Brand (0 to cancel): ", updated.brand,
                          MAX_BRAND_LEN);
          if (strcmp(updated.brand, "0") == 0) {
            printf("Action cancelled.\n");
            break;
          }

          if (get_safe_float("Enter New Price (0 to cancel): ",
                             &updated.price) == 0) {
            printf("Action cancelled.\n");
            break;
          }

          if (get_safe_int("Enter New Stock Quantity (0 to cancel): ",
                           &updated.stock_quantity) == 0) {
            printf("Action cancelled.\n");
            break;
          }

          if (update_product(products, product_count, update_id, &updated) !=
              0) {
            printf("Product updated successfully!\n");
          } else {
            printf("Failed to update product due to validation errors.\n");
          }
          break;
        }
        case 4: {
          printf("\n--- Delete Product ---\n");
          int delete_id = 0;
          if (get_safe_int("Enter Product ID to Delete (0 to cancel): ",
                           &delete_id) == 0) {
            printf("Action cancelled.\n");
            break;
          }

          if (delete_product(products, &product_count, delete_id, bundles,
                             bundle_count) != 0) {
            printf("Product deleted successfully!\n");
          } else {
            printf("Failed to delete product.\n");
          }
          break;
        }
        default:
          printf("Invalid option. Please try again.\n");
          break;
        }
      }
      break;
    }
    case 2:
      printf("Bundle management is not implemented yet.\n");
      break;
    case 3:
      printf("Revenue and reports are not implemented yet.\n");
      break;
    case 4:
      if (save_database(products, product_count, bundles, bundle_count, orders,
                        order_count, &admin) != 0) {
        printf("Database saved successfully!\n");
      } else {
        printf("Database save completed.\n");
      }
      break;
    default:
      printf("Invalid option. Please try again.\n");
      break;
    }
  }
}

void run_menu_system(void) {
  load_database(products, &product_count, bundles, &bundle_count, orders,
                &order_count, &admin);

  /* Initialize sample products if empty */
  if (product_count == 0) {
    Product p1 = {101, "iPhone 15 Pro", "Phone", "Apple", 999.99F, 10};
    Product p2 = {102, "ThinkPad X1 Carbon", "Laptop", "Lenovo", 1499.99F, 5};
    Product p3 = {103, "iPad Air", "Tablet", "Apple", 599.99F, 8};
    add_product(products, &product_count, &p1);
    add_product(products, &product_count, &p2);
    add_product(products, &product_count, &p3);
  }

  if (is_admin_setup_complete() == 0) {
    printf("==========================================\n");
    printf("        ADMIN CREDENTIALS SETUP           \n");
    printf("==========================================\n");
    char username[MAX_USERNAME_LEN] = {0};
    char password[MAX_PASSWORD_LEN] = {0};
    int setup_done = 0;
    while (setup_done == 0) {
      get_safe_string("Create Admin Username (0 to cancel): ", username,
                      MAX_USERNAME_LEN);
      if (strcmp(username, "0") == 0) {
        printf("Setup cannot be cancelled. Admin setup is mandatory.\n");
        continue;
      }
      get_safe_string("Create Admin Password (0 to cancel): ", password,
                      MAX_PASSWORD_LEN);
      if (strcmp(password, "0") == 0) {
        printf("Setup cannot be cancelled. Admin setup is mandatory.\n");
        continue;
      }

      if (strlen(username) < 4 || strchr(username, ' ') != NULL) {
        printf("Invalid username. Must be at least 4 characters and contain no "
               "spaces.\n");
        continue;
      }
      if (strlen(password) < 4 || strchr(password, ' ') != NULL) {
        printf("Invalid password. Must be at least 4 characters and contain no "
               "spaces.\n");
        continue;
      }

      if (setup_admin_credentials(username, password) != 0) {
        printf("Admin credentials saved successfully!\n");
        setup_done = 1;
      } else {
        printf("Error: Failed to write credentials file. Try again.\n");
      }
    }
  }

  display_customer_menu();
}
