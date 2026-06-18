# Pull Request: feat-story-5.0-prod-crud-back

## Description
Implements the core backend database array functions for managing electronics products. This includes:
- Unique ID validations and positive constraint checks.
- Category verification strictly matching `"Phone"`, `"Laptop"`, `"Tablet"`, or `"Accessory"`.
- Real-time boundaries checking for price (`> 0.0`) and stock quantity (`>= 0`).
- Element shifting to the left during product deletion to maintain array contiguity.
- Blocked product deletion when linked to active bundles, including print warnings listing all referencing bundle IDs and names.
- Contoured console tabular formatting for inventory catalog output.

## Story Reference
* Resolves Story: #5

## Checklist
- [x] Code compiles without warnings on target platform (`clang -std=c17 -m64`)
- [x] Code formatted using `clang-format`
- [x] Code checked using `clang-tidy`
- [x] Data validation handles edge cases correctly (no negative numbers, no overflow)
- [x] User input can be cancelled by pressing `0`

## Manual Verification Results
We compiled the source under the strict target flags `clang -std=c17 -m64 -Wall -Wextra -Wpedantic ...` and validated the functionality with a test suite covering the edge cases:

### Execution Trace Logs
```text
=== RUNNING PRODUCT CRUD TESTS ===

[TEST 1.1] Adding valid products...
p1 added ok. Count = 1
p2 added ok. Count = 2
p3 added ok. Count = 3
p4 added ok. Count = 4

[TEST 1.2] Adding duplicate ID (should fail)...
Error: Product ID 1 already exists.
Duplicate ID blocked correctly.

[TEST 1.3] Adding invalid category (should fail)...
Error: Invalid category 'Gadget'. Category must strictly be one of: Phone, Laptop, Tablet, Accessory.
Invalid category blocked correctly.

[TEST 1.4] Adding invalid price (should fail)...
Error: Price must be a positive float value (> 0.0).
Zero price blocked correctly.

[TEST 1.5] Adding invalid stock (should fail)...
Error: Stock quantity must be non-negative (>= 0).
Negative stock blocked correctly.

[TEST 2.1] Find existing product (ID 2)...
Found correctly at index 1: ThinkPad T14

[TEST 2.2] Find non-existing product (ID 99)...
Correctly returned -1 for non-existing ID.

[TEST 3.1] Updating product (ID 2)...
Update success. New details: ThinkPad T14 Gen 4, Price: $1199.99, Stock: 12

[TEST 3.2] Updating product with invalid Category (should fail)...
Error: Invalid category 'Gadget'. Category must strictly be one of: Phone, Laptop, Tablet, Accessory.
Bad category update blocked correctly.

[TEST 3.3] Updating product to duplicate existing ID (should fail)...
Error: Product ID 3 already exists.
Duplicate ID update blocked correctly.

[TEST 4.1] Displaying all products...
ID     | Name                           | Category     | Brand                | Price      | Stock   
------------------------------------------------------------------------------------------------------
1      | iPhone 15                      | Phone        | Apple                | $999.99    | 50      
2      | ThinkPad T14 Gen 4             | Laptop       | Lenovo               | $1199.99   | 12      
3      | iPad Air                       | Tablet       | Apple                | $599.00    | 20      
4      | USB-C Cable                    | Accessory    | Generic              | $9.99      | 100     

[TEST 5.1] Deleting product ID 1 (active in bundle 201 - should block)...
Cannot delete product. It is part of active bundles:
- Bundle ID: 201, Name: Starter Kit
Blocked successfully!

[TEST 5.2] Deleting product ID 2 (active in bundle 202 - should block)...
Cannot delete product. It is part of active bundles:
- Bundle ID: 202, Name: Office Combo
Blocked successfully!

[TEST 5.3] Deleting product ID 4 (not in any bundle - should succeed)...
Deleted successfully! Count: 4 -> 3

[TEST 5.4] Displaying products after deletion...
ID     | Name                           | Category     | Brand                | Price      | Stock   
------------------------------------------------------------------------------------------------------
1      | iPhone 15                      | Phone        | Apple                | $999.99    | 50      
2      | ThinkPad T14 Gen 4             | Laptop       | Lenovo               | $1199.99   | 12      
3      | iPad Air                       | Tablet       | Apple                | $599.00    | 20      

[TEST 6.1] Enforcing MAX_PRODUCTS limit...
Filled up to current count = 100
Error: Maximum product limit reached (100).
Overflow product blocked correctly when count = 100

=== TESTS COMPLETED ===
```
