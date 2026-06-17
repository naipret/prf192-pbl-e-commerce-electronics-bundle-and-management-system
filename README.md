# PRF192 Project - E-Commerce Electronics & Bundle Management System

This system provides backend and inventory controls for managing single electronic items and combination discount bundles. It has been built and structured under the C17 standard.

---

## 1. Directory Blueprint

* `bin/`: Holds the compiled executables.
* `obj/`: Holds intermediary object binary files.
* `include/`: Folder containing modular header declarations.
* `src/`: Folder containing modular implementation source files.
* `Makefile`: Automates compiler actions under strict warning conditions.
* `docs/`: System documentation including requirements, architecture, test designs, and agile backlogs.

---

## 2. Compilation Instructions

### Native Platform Build

Execute the following build routine in your terminal:

```bash
make clean
make all
```

### Formatting and Linting Checks

Ensure your code complies with project quality checks before pushing:

```bash
make format
make tidy
```

---

## 3. Product Features & Operations

1. **Admin Credentials Management**: Detects missing login records on boot to guide Admin profile registration.
2. **Product Inventory Controls**: Supports unique item records and categories mapping.
3. **Dynamic Bundle Calculations**: Dynamically resolves combined prices and virtual stock levels.
4. **Order Logging & Deductions**: Implements transaction stock deductions.
5. **Business Intelligence Reporting**: Tracks cumulative sales statistics.

---

## 4. CI/CD & Release Pipeline

The project uses GitHub Actions to automate builds and releases.

* **Workflow File**: `.github/workflows/build-and-release.yml`
* **Execution Environment**: Windows runner using MSYS2 setup with MinGW UCRT64.
* **Compilation Command**: Compiles C17 codebase with `-O2` optimizations directly to `bin/prf192-pbl-e-commerce-electronics-bundle-and-management-system.exe`.
* **Releases**: Pushes to `main` compile and release under the `latest` tag, while tagged releases (e.g., `v1.0.0`) publish formal draft releases on GitHub.

---

## 5. Development & Contribution Standards

To work on this project, please consult [CONTRIBUTING.md](CONTRIBUTING.md) for full style constraints.
