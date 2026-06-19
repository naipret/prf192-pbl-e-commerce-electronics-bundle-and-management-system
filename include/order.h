#ifndef ORDER_H
#define ORDER_H

#include "types.h"

/**
 * @brief Validates and places a new order.
 *
 * Verifies that the requested product or bundle ID exists, checks that
 * stock levels are sufficient, deducts the stock, calculates the total price,
 * stamps the order date, generates an order ID if needed, and inserts the
 * order into the orders array.
 *
 * @param orders Array of order structures.
 * @param count Pointer to the current number of active orders. Will be
 * incremented on success.
 * @param products Array of product structures.
 * @param product_count Current number of active products.
 * @param bundles Array of bundle structures.
 * @param bundle_count Current number of active bundles.
 * @param new_order Pointer to the order containing details of the order
 * request.
 * @return 1 if the order is successfully placed, 0 otherwise.
 */
int create_order(Order orders[], int *count, Product products[],
                 int product_count, const Bundle bundles[], int bundle_count,
                 const Order *new_order);

/**
 * @brief Displays the history of all placed orders in a structured table.
 *
 * @param orders Array of order structures.
 * @param count Current number of active orders.
 */
void display_order_history(const Order orders[], int count);

/**
 * @brief Prints a revenue report summarizing the total sales.
 *
 * @param orders Array of order structures.
 * @param order_count Current number of active orders.
 * @param products Array of product structures.
 * @param product_count Current number of active products.
 * @param bundles Array of bundle structures.
 * @param bundle_count Current number of active bundles.
 */
void print_revenue_report(const Order orders[], int order_count,
                          const Product products[], int product_count,
                          const Bundle bundles[], int bundle_count);

#endif /* ORDER_H */
