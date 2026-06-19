# GitHub Project Card: Story 7.2 - Best-Selling Item Calculations

## 📋 Description

Build lookup algorithms to analyze order patterns and identify the best-selling product and bundle.

## 🛠️ Files to Modify/Create

* **Modify**: [src/order.c](../../../src/order.c)

## 📖 Global References

* Consult reporting requirements in [PRD.md](../../../docs/requirements.md#35-analytics--statistical-reports-admin-only).
* Refer to struct fields in `types.h`.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Implement Best Selling Product logic: sums quantities sold for each unique Product ID in the order log, and prints the name and total quantity of the highest product.
* [ ] Implement Best Selling Bundle logic: sums quantities sold for each unique Bundle ID in the order log, and prints the name and total quantity of the highest bundle.
* [ ] Ensure the algorithm handles empty lists or ties (multiple items sharing the same highest sales count) gracefully.
