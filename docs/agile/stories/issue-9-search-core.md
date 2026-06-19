# GitHub Project Card: Story 5.1 - Database Search & Category Filters

## 📋 Description

Build lookup filters for products. Allow customers and administrators to query database items by partial names or matching categories.

## 🛠️ Files to Modify/Create

* **Modify**: [include/product.h](../../../include/product.h)
* **Modify**: [src/product.c](../../../src/product.c)

## 📖 Global References

* Consult search rules inside [PRD.md](../../../docs/requirements.md#33-search-formatting-customer--admin).
* Use the lowercase converter string utility from Story 1.2.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Implement case-insensitive partial substring matching (e.g. "air" matches "MacBook Air").
* [ ] Filter products by category (matches exact string, returning all matches).
* [ ] Filter products by price range: displays all products satisfying $min\_price \le price \le max\_price$.
* [ ] Ensure all search screens output clean, formatted tables or return "No products found."
