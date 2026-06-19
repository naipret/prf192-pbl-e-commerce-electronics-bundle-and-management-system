# GitHub Project Card: Story 8.1 - Transactional Safe Persistence Files

## 📋 Description

Build safe file reading and writing routines. Prevent database file corruption on crashes by implementing step-by-step backup swaps.

## 🛠️ Files to Modify/Create

* **Modify**: [include/file_io.h](../../../include/file_io.h)
* **Modify**: [src/file_io.c](../../../src/file_io.c)

## 📖 Global References

* Consult the transaction workflow in [PRD.md](../../../docs/requirements.md#5-safe-persistence--transactional-io).
* Use system functions like `rename` and `remove` cleanly. Ensure all files are closed before modifying paths.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Implement `save_database()`: writes records to `.tmp` files (e.g. `products.tmp`).
* [ ] If the `.tmp` write is successful, rename the active database files (e.g. `products.txt`) to backup files (e.g. `products.bak`).
* [ ] Promote `products.tmp` to `products.txt`.
* [ ] Implement `load_database()`: reads database records from `products.txt` and restores arrays.
* [ ] If reading `products.txt` fails, check if `products.bak` exists, restore it, and load data from the backup with a warning message.
