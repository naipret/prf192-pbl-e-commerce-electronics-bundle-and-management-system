# GitHub Project Card: Story 7.3 - Low-Stock Warnings Alert System

## 📋 Description

Build an automatic inventory warning alert to help administrators check which items require restocking.

## 🛠️ Files to Modify/Create

* **Modify**: [src/order.c](../../../src/order.c)

## 📖 Global References

* Consult reporting requirements in [PRD.md](../../../docs/requirements.md#35-analytics--statistical-reports-admin-only).
* Refer to struct fields in `types.h`.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Iterate through all products in the database array.
* [ ] Display a warning message containing the Product ID, Name, and current stock for all items with a `stock_quantity` strictly less than 5.
* [ ] If no items have stock levels $< 5$, display "All products have sufficient stock levels."
