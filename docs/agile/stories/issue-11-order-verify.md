# GitHub Project Card: Story 6.1 - Order Request Validation

## 📋 Description

Build order placement validations. Verify that the requested product or bundle ID exists, and check that stock levels are sufficient.

## 🛠️ Files to Modify/Create

* **Modify**: [include/order.h](../../../include/order.h)
* **Modify**: [src/order.c](../../../src/order.c)

## 📖 Global References

* Consult checkout rules in [PRD.md](../../../docs/requirements.md#34-order-processing-customer--admin).
* Integrate `get_virtual_bundle_stock()` from Story 4.2.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Order requests require Customer Name, Item ID, type flag (Product or Bundle), and Quantity.
* [ ] Validate that Product ID exists in `products[]` or Bundle ID exists in `bundles[]`.
* [ ] Verify stock: if product, `stock_quantity >= quantity`; if bundle, `virtual_stock >= quantity`.
* [ ] If stock check fails, reject the order and print an error message indicating the insufficient items.
