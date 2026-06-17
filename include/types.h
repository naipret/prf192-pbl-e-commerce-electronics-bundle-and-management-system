#ifndef TYPES_H
#define TYPES_H

// Core limits
#define MAX_PRODUCTS 100
#define MAX_BUNDLES 50
#define MAX_ORDERS 200
#define MAX_BUNDLE_ITEMS 10

// String lengths
#define MAX_NAME_LEN 100
#define MAX_CAT_LEN 50
#define MAX_BRAND_LEN 50
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_DATE_LEN 20

// Admin credential structure
typedef struct {
  char username[MAX_USERNAME_LEN];
  char password[MAX_PASSWORD_LEN];
  int is_setup;
} AdminCredentials;

// Product inventory structure
typedef struct {
  int product_id;
  char product_name[MAX_NAME_LEN];
  char category[MAX_CAT_LEN];
  char brand[MAX_BRAND_LEN];
  float price;
  int stock_quantity;
} Product;

// Bundle composition structure
typedef struct {
  int bundle_id;
  char bundle_name[MAX_NAME_LEN];
  int product_ids[MAX_BUNDLE_ITEMS];
  int product_count;
  float discount_rate;
  float bundle_price;
} Bundle;

// Order entry structure
typedef struct {
  int order_id;
  char customer_name[MAX_NAME_LEN];
  int item_id;
  int is_bundle; // 0 = product, 1 = bundle
  int quantity;
  float total_price;
  char order_date[MAX_DATE_LEN];
} Order;

#endif /* TYPES_H */
