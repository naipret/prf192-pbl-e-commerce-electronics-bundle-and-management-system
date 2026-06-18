# GitHub Project Card: Story 7.1 - Financial Sales & Revenue Summaries

## 📋 Description

Build analytics functions to calculate and report financial metrics to administrators.

## 🛠️ Files to Modify/Create

* **Modify**: [include/order.h](../../../include/order.h)
* **Modify**: [src/order.c](../../../src/order.c)

## 📖 Global References

* Consult reporting requirements in [PRD.md](../../../docs/requirements.md#35-analytics--statistical-reports-admin-only).
* Refer to struct fields in `types.h`.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Implement revenue calculations: sum the `total_price` of all completed orders.
* [ ] Print total revenue formatted to two decimal places (e.g. `$1,234.50`).
* [ ] Report total count of products sold and total count of bundles sold.
