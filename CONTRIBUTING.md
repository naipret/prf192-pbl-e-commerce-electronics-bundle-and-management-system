# Developer Contribution & Workflow Guidelines

Welcome to the team! To maintain high code quality and smooth Git operations across our 4-person Agile group, please strictly follow these development rules.

---

## 1. Branch Naming Conventions

We use flat hyphenated naming conventions. **Do not use subdirectories (no `/` in branch names).**

* **Feature Branches**: `feat-story-X-description` (e.g., `feat-story-1-product-crud`)
* **Bugfix Branches**: `fix-story-X-description` (e.g., `fix-story-3-infinite-loop`)
* **Documentation Branches**: `docs-story-X-description` (e.g., `docs-story-4-io-guide`)

---

## 2. Pull Request (PR) Policy

Before any branch is merged into `main`, you must submit a Pull Request. Another team member must review the PR and the CI build must pass.

### Pull Request Template

```markdown
# Pull Request: [feat|fix|docs]-story-X-description

## Description
Brief description of the changes introduced by this pull request.

## Story Reference
* Resolves Story X: [Story Title]

## Checklist
- [ ] Code compiles without warnings on target platform (`clang -std=c17 -m64`)
- [ ] Code formatted using `clang-format`
- [ ] Code checked using `clang-tidy`
- [ ] Data validation handles edge cases correctly (no negative numbers, no overflow)
- [ ] User input can be cancelled by pressing `0`

## Manual Verification Results
Insert console outputs or testing trace proving correct behavior.
```

### Sample Pull Request

```markdown
# Pull Request: feat-story-1-product-crud

## Description
Implements the core CRUD functionalities for product structures, including array insertion, validation of unique IDs, category verification, price boundaries, and shifted array deletions.

## Story Reference
* Resolves Story 1: Product CRUD Management

## Checklist
- [x] Code compiles without warnings on target platform (`clang -std=c17 -m64`)
- [x] Code formatted using `clang-format`
- [x] Code checked using `clang-tidy`
- [x] Data validation handles edge cases correctly
- [x] User input can be cancelled by pressing `0`

## Manual Verification Results
- Add Product Action:
  - Enter Product ID (0 to cancel): 101
  - Enter Product Name: Smartphone X
  - Enter Product Category (Phone/Laptop/Tablet/Accessory): Phone
  - Enter Brand: Apple
  - Enter Price: 899.99
  - Enter Stock: 45
- Result: Product ID 101 added successfully!
```

---

## 3. Commit Message Guidelines

We follow **Conversational Commits** to keep git log entries structured and readable:

```markdown

<type>(<scope>): <short description>

```

* **Types**:
  * `feat`: A new feature implementation
  * `fix`: A bug fix
  * `docs`: Documentation updates only
  * `style`: Styling/formatting changes (no logic changes)
  * `refactor`: Restructuring code (no new features or fixes)
  * `test`: Adding or editing test scripts
* **Scope**: The file or module being changed (e.g., `product`, `bundle`, `file_io`).
* **Example**:
  * `feat(product): add product array insertion and ID checks`
  * `fix(menu): correct scanf buffer flush infinite loop`
  * `docs(readme): update build commands`

---

## 4. Coding & Clean Code Standards

### 4.1. Code Formatting & Linting

* **Format Command**: `clang-format -i include/*.h src/*.c`
* **Linting Command**: `clang-tidy src/*.c -- -Iinclude`
* Ensure your editor is configured to use the LLVM style specified in [.clang-format](.clang-format).

### 4.2. Header Guards & Comments

* All header files inside `include/` must contain `#ifndef` / `#define` header guards derived from their filename:

  ```c
  #ifndef MODULE_NAME_H
  #define MODULE_NAME_H

  // Declarations here

  #endif /* MODULE_NAME_H */
  ```

* Write clear, concise comments. Use Doxygen-style documentation headers above function declarations in headers:

  ```c
  /**
   * @brief Searches for a product using case-insensitive name matching.
   * @param products Array of product structures.
   * @param count Current number of active products.
   * @param query The string to search for.
   * @return The array index of the matching product, or -1 if not found.
   */
  int search_product_by_name(const Product products[], int count, const char *query);
  ```

### 4.3. Standard Library Constraints & Safety Rules

* **Unsafe Buffer Control**: Never use raw `gets()`. Use `fgets()` with designated bounds.
* **Menu Input Integrity**: Do not read numbers directly using `scanf("%d")` because non-numeric characters trigger infinite loops. Always read lines with `fgets()` and parse with `strtol()` / `strtod()`.
* **Parameter Integrity**: Use the `const` modifier for arrays and strings passed to functions that should not modify the data (e.g., print/search functions).

---

## 5. Development Build Commands

Ensure you compile using these flags to verify compliance:

```bash
clang -std=c17 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 \
-Wformat-security -Wfloat-equal -Wundef -Wsign-conversion -Wcast-align \
-Wcast-qual -Wmissing-prototypes -Wmissing-declarations -Wunreachable-code \
-Wnull-dereference -Wimplicit-fallthrough -Wswitch-enum -Wpointer-arith \
-Iinclude src/*.c -o app
```
