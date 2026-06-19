# GitHub Project Card: Story 4.2 - Bundle Pricing & Virtual Stock Calculation

## 📋 Description

Implement runtime calculations for bundles. Virtual stock levels and prices must be computed dynamically by lookup queries rather than stored statically.

## 🛠️ Files to Modify/Create

* **Modify**: [src/bundle.c](../../../src/bundle.c)

## 📖 Global References

* Consult formulas inside [PRD.md](../../../docs/requirements.md#32-dynamic-bundle-management-admin-only).
* Depend on Product and Bundle structs from `types.h`.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Implement `get_virtual_bundle_stock()`: loops through all product IDs inside the bundle, looks up their stock levels, and returns the minimum stock quantity.
* [ ] Implement `calculate_bundle_price()`: sums prices of all child items, applies the discount rate, and returns the discounted total.
* [ ] Integrate dynamic price and virtual stock calculations whenever displaying the bundle catalog.
