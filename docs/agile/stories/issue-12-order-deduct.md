# GitHub Project Card: Story 6.2 - Inventory Stock Deduction & Logging

## 📋 Description

Implement atomic stock adjustment logic. Deduct stock levels correctly and log completed order records.

## 🛠️ Files to Modify/Create

* **Modify**: [src/order.c](../../../src/order.c)

## 📖 Global References

* Consult inventory adjustments inside [PRD.md](../../../docs/requirements.md#34-order-processing-customer--admin).
* Refer to structure layouts in `types.h`.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Atomic stock check must pass before deducting any stock (preventing partial stock deductions if an item runs out halfway).
* [ ] If buying a single product: subtract quantity directly from the product's `stock_quantity`.
* [ ] If buying a bundle: subtract quantity from the `stock_quantity` of **all** products inside that bundle.
* [ ] Log a new Order record: generate a unique ID, calculate total price (applying discount if bundle), and write the date in `YYYY-MM-DD` format.
* [ ] Enforce array limits (`MAX_ORDERS=200`).
