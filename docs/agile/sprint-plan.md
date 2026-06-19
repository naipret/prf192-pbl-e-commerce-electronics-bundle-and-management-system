# Sprint Backlog & Team Plan

This document maps the 9 Epics into concrete Agile stories. The stories are divided among the 4 team members to enable concurrent development, structured review, and successful integration.

---

## Team Role Assignments

| Assignee | Primary Responsibility | Assigned Stories |
|---|---|---|
| **Member 1 (Lead)** | Infrastructure, Security & CLI Navigation | Story 1.1, Story 2.1, Story 9.1 |
| **Member 2** | Product Inventory CRUD & Search / Sorting | Story 3.1, Story 5.1 |
| **Member 3** | Bundle Architecture & BI Reports | Story 4.1, Story 7.1 |
| **Member 4** | Order Processing, Safe Storage & DevOps | Story 6.1, Story 8.1, Story 10.1 |

---

## Detailed Story Backlog

### Quality Infrastructure & Safe Input Library

* **Assignee**: Member 1
* **Description**: Create compile directives, clang formatter configs, and robust console inputs wrappers inside `utils.c` and `utils.h`. This library will prevent invalid float/int inputs from causing infinite loops and standardizes console buffer clearing.
* **Acceptance Criteria**:
  * [ ] Compilation runs cleanly using `clang -std=c17 -m64` with strict diagnostic flags.
  * [ ] Calling `get_safe_int()` reads input via `fgets` and safely converts via `strtol`. Returns success status.
  * [ ] Calling `get_safe_float()` parses inputs using `strtod`.
  * [ ] Buffer clearing handles inputs exceeding target string array sizes safely.
  * [ ] Code conforms to LLVM styling checks.

---

### Admin Registration Setup & Security Login

* **Assignee**: Member 1
* **Description**: Implement first-run detection protocols. If credentials files do not exist, force registration. Create credential check logic with maximum attempts limits and cancel overrides.
* **Acceptance Criteria**:
  * [ ] On app start, check for existence of `admin.txt`. If missing, initiate registration mode.
  * [ ] Admin Setup requires entering username and password (minimum length 4, no whitespace).
  * [ ] In Admin Mode option, require username and password verification.
  * [ ] Entering `0` during login cancels the prompt and falls back to Customer Menu.
  * [ ] Restrict login retry failures to 3 before locking access.

---

### Product Database CRUD Management

* **Assignee**: Member 2
* **Description**: Create product structures and implement data modification logic. Products must be stored in a static array with size bounds check.
* **Acceptance Criteria**:
  * [ ] `add_product()` validates product ID is unique and greater than 0.
  * [ ] Category field must match one of: `"Phone"`, `"Laptop"`, `"Tablet"`, `"Accessory"`.
  * [ ] Price must be greater than 0. Stock quantity must be 0 or higher.
  * [ ] `delete_product()` is blocked if the product ID is associated with any active bundle.
  * [ ] Array size limits are enforced (max 100 products). If full, reject additions gracefully.

---

### Dynamic Bundle Design & Virtual Stock Calculation

* **Assignee**: Member 3
* **Description**: Define the Bundle struct. Implement adding products to bundle lists, duplicate protection, and calculate dynamic prices and virtual stock levels.
* **Acceptance Criteria**:
  * [ ] Bundles store array of component product IDs (maximum 10).
  * [ ] `get_virtual_bundle_stock()` dynamically looks up product stocks and returns the minimum stock.
  * [ ] `calculate_bundle_price()` applies `discount_rate` (validated $0.0 \le rate \le 1.0$) to the sum of items.
  * [ ] Duplicate product IDs in the same bundle are rejected with a warning.
  * [ ] Standardizing bundle displays to show both name, discount percentage, and sub-items list.

---

### Database Search & Bubble Sort Filters

* **Assignee**: Member 2
* **Description**: Implement product lookup capabilities. Includes case-insensitive name matching and Bubble Sort algorithms for sorting results.
* **Acceptance Criteria**:
  * [ ] Case-insensitive partial name matching works using `to_lowercase` and `strstr`.
  * [ ] Category filtering displays all matching products in a aligned table.
  * [ ] Bubble sort is written to sort products by price (ascending/descending) and alphabetically by name.

---

### Order Creation & Inventory Stock Deductions

* **Assignee**: Member 4
* **Description**: Develop checkout routines. Orders can be single products or bundle combos. Stock adjustments must be computed correctly, deducting items individually.
* **Acceptance Criteria**:
  * [ ] Customer enters Customer Name, ID of item, and target quantity.
  * [ ] System verifies stock availability (individual product stock $\ge$ quantity, or virtual bundle stock $\ge$ quantity).
  * [ ] If valid, deducts quantity from product stock (for single product) or from **all** sub-items' stock (for bundle).
  * [ ] Generates unique Order ID and stamps the current system date in format `YYYY-MM-DD`.

---

### Business Intelligence Sales Reporting

* **Assignee**: Member 3
* **Description**: Read order logs to calculate business revenue summaries.
* **Acceptance Criteria**:
  * [ ] Total Revenue sums the final transaction values of all logged orders.
  * [ ] Best Selling Product returns the ID + name with the highest cumulative sold counts.
  * [ ] Best Selling Bundle returns the bundle ID + name with the highest cumulative sold counts.
  * [ ] Alert function lists products with stock levels below 5.

---

### Safe Transactional I/O Persistence

* **Assignee**: Member 4
* **Description**: Implement file load and save features with fail-safe transactions to prevent data corruption.
* **Acceptance Criteria**:
  * [ ] Data is saved by writing to temporary `.tmp` files first.
  * [ ] Upon success, renames current active `.txt` files to `.bak` backups.
  * [ ] Renames `.tmp` files to final active `.txt` database files.
  * [ ] On load failure, fall back to `.bak` files automatically, printing a warning.

---

### Console UI Layouts & Escape Handlers

* **Assignee**: Member 1
* **Description**: Set up the main CLI menus. Implement screen output borders, clean grid tabulations, and the unified escape key `0`.
* **Acceptance Criteria**:
  * [ ] Main Menu routes to Role Selection or exits.
  * [ ] Customer Menu contains: Browse catalog, Search/Sort, Order Checkout, Admin Login, and Exit.
  * [ ] Admin Menu contains: Product CRUD, Bundle CRUD, Analytics, Save, and Log out.
  * [ ] Typing `0` in any input loops aborts the action and cleanly moves back up the menu level.

---

### DevOps Build Configurations

* **Assignee**: Member 4
* **Description**: Integrate the optional multi-stage Docker build container and setup the GitHub Action CI build pipeline.
* **Acceptance Criteria**:
  * [ ] `Dockerfile` builds a static C binary in the build stage and runs it in a minimal runtime container.
  * [ ] GitHub workflow config `.github/workflows/ci.yml` triggers on push to `main` and Pull Requests.
  * [ ] CI compiles codebase with strict Clang flags and checks code formatting and lints.
