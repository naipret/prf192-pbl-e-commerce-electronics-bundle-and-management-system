# GitHub Project Card: Story 2.1 - First-Run Admin Setup & Registration

## 📋 Description

Build credentials database tracking. Upon program initialization, detect if the admin credentials record is empty/absent. If so, force a mandatory registration wizard to secure subsequent runs.

## 🛠️ Files to Modify/Create

* **Modify**: [include/admin.h](../../../include/admin.h)
* **Modify**: [src/admin.c](../../../src/admin.c)

## 📖 Global References

* Consult password rules inside the [PRD.md](../../../docs/requirements.md#21-first-run-setup-process).
* Use the safe input functions in `utils.h` from Story 1.2.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] `is_admin_setup_complete()` returns `0` if credentials file (`admin.txt`) doesn't exist, and `1` if it exists.
* [ ] Registration Wizard requires entering a username and password (at least 4 characters, non-empty, and free of whitespace).
* [ ] Obfuscate the password before saving (e.g. simple XOR cipher using a constant mask like `0x5A`) so it is not visible in plaintext in `admin.txt`.
* [ ] Typing `0` at registration username prompt cancels and prompts warning, preventing bypass. Setup is mandatory.
