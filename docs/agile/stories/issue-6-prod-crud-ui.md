# GitHub Project Card: Story 3.2 - Product Catalog Aligned CLI Views

## 📋 Description

Build terminal user interfaces for managing products. Design clean column widths, header borders, and navigation options.

## 🛠️ Files to Modify/Create

* **Modify**: [src/product.c](../../../src/product.c)
* **Modify**: [src/menu.c](../../../src/menu.c)

## 📖 Global References

* Consult layout requirements inside [PRD.md](../../../docs/requirements.md#5-safe-persistence--transactional-io) and [CONTRIBUTING.md](../../../CONTRIBUTING.md#42-header-guards-and-comments).

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Display catalogs in a clean tabulated grid with padded columns (ID, Name, Category, Brand, Price, Stock).
* [ ] Integrate user prompting flow inside `src/menu.c` for Admin CRUD triggers.
* [ ] Double check all screens display clean prompt texts and handle exit key `0` correctly.
