# GitHub Project Card: Story 2.2 - Admin Verification & Session Authentication

## 📋 Description

Build the password verification flow. Provide entry validation screens when users try to log into Admin Mode. Ensure security limits and quick exit procedures.

## 🛠️ Files to Modify/Create

* **Modify**: [include/admin.h](../../../include/admin.h)
* **Modify**: [src/admin.c](../../../src/admin.c)

## 📖 Global References

* Consult the authentication flowchart in [PRD.md](../../../docs/requirements.md#2-user-roles--access-control).
* Use the safe input functions in `utils.h` from Story 1.2.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Implement `verify_admin_login(const char *username, const char *password)`: applies the XOR obfuscation step on the entered password, compares it to the obfuscated values in `admin.txt`, and returns `1` if correct.
* [ ] Limit authentication loops to a maximum of 3 failed password attempts.
* [ ] On the third failure, block entry to Admin mode and return user safely to Customer Menu.
* [ ] Ensure entering `0` at username or password prompt immediately exits the login sequence.
