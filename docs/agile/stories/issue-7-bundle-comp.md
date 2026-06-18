# GitHub Project Card: Story 4.1 - Dynamic Bundle Composition & Logic

## 📋 Description

Build C structures for combination bundles. Implement dynamic subcomponent listing and discount rate verification rules.

## 🛠️ Files to Modify/Create

* **Modify**: [include/bundle.h](../../../include/bundle.h)
* **Modify**: [src/bundle.c](../../../src/bundle.c)

## 📖 Global References

* Consult bundle specs inside [PRD.md](../../../docs/requirements.md#32-dynamic-bundle-management-admin-only).
* Use global definitions from `types.h`.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Bundle holds a static array of up to 10 unique product IDs.
* [ ] `add_product_to_bundle()` checks if the product ID already exists in the bundle, blocking duplicate items with a warning message.
* [ ] Verify bundle discount rate is bounded ($0.0 \le rate \le 1.0$).
* [ ] `remove_product_from_bundle()` removes products and shifts remaining items.
* [ ] Bundles must contain at least 1 product. Empty bundles are deleted or blocked from creation.
