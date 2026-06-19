# GitHub Project Card: Story 1.1 - Quality Build Infrastructure

## 📋 Description

Configure the build system, compile flags, target output directories (`obj/` for object files, `bin/` for binaries), and global configuration headers to ensure clean, standard-compliant builds.

## 🛠️ Files to Modify/Create

* **Modify**: [Makefile](../../../Makefile)
* **Create**: [include/types.h](../../../include/types.h)

## 📖 Global References

* Consult the repository coding standards in [CONTRIBUTING.md](../../../CONTRIBUTING.md) for compilation flags.
* Consult the directory blueprint in [docs/readme.md](../../../docs/readme.md).

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] The `Makefile` successfully segregates compilation outputs: `.o` files are stored in `obj/`, and final binaries are stored in `bin/`.
* [ ] Directory creation rules in the `Makefile` must run correctly on both Windows (Cmd/Git Bash) and Linux without shell-dependency crashes.
* [ ] `include/types.h` must contain all global limit definitions: `MAX_PRODUCTS=100`, `MAX_BUNDLES=50`, `MAX_ORDERS=200`, `MAX_BUNDLE_ITEMS=10`.
* [ ] Struct definitions for `Product`, `Bundle`, `Order`, and `AdminCredentials` must be defined solely in `types.h` to avoid circular inclusion locks.
* [ ] Clean target `make clean` deletes `obj/` and `bin/` cleanly on all OS platforms.
