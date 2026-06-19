# GitHub Project Card: Story 3.1 - Product Inventory CRUD Database Logic

## 📋 Description

Develop product record data models and array functions. Store data in a static array with size bounds check. Provide data validations to ensure catalog accuracy.

## 🛠️ Files to Modify/Create

* **Modify**: [include/product.h](../../../include/product.h)
* **Modify**: [src/product.c](../../../src/product.c)

## 📖 Global References

* Consult product specs inside [PRD.md](../../../docs/requirements.md#31-product-management-admin-only).
* Consult naming rules inside [.clang-tidy](../../../.clang-tidy).

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] `add_product()` checks for unique ID constraints (cannot duplicate existing IDs).
* [ ] Verify that product Category string belongs strictly to: `"Phone"`, `"Laptop"`, `"Tablet"`, `"Accessory"`.
* [ ] Price must be a positive float value ($> 0.0$). Stock quantity must be non-negative ($\ge 0$).
* [ ] `delete_product()` removes products by shifting remaining items left.
* [ ] Ensure `delete_product()` is BLOCKED if the product ID is part of an active bundle array. Print a warning containing the IDs and Names of all active bundles that contain that product.
* [ ] Enforce array limits (`MAX_PRODUCTS=100`). Reject insertions if maximum is reached.
