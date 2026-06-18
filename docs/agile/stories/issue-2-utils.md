# GitHub Project Card: Story 1.2 - Safe Console Input Utility Library

## 📋 Description

Create a secure console input wrapper library that handles reading lines via `fgets` and parsing numbers via `strtol`/`strtod`. This shields the system from standard library bugs (such as `scanf` infinite loops on invalid chars) and flushes the buffer correctly.

## 🛠️ Files to Modify/Create

* **Modify**: [include/utils.h](../../../include/utils.h)
* **Modify**: [src/utils.c](../../../src/utils.c)

## 📖 Global References

* Consult safe standard library rules inside [CONTRIBUTING.md](../../../CONTRIBUTING.md#43-standard-library-constraints--safety-rules).
* Consult [architecture.md](../../../docs/architecture.md#26-robust-input-utility-includeutilsh) for method layouts.

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Implement `get_safe_int(const char *prompt, int *out_value)`: prints prompt, reads line via `fgets`, strips `\n`, converts via `strtol` (checking that the entire string was parsed successfully), and checks bounds.
* [ ] Implement `get_safe_float(const char *prompt, float *out_value)`: performs identical checks converting via `strtod`.
* [ ] Implement `get_safe_string(const char *prompt, char *out_str, int max_len)`: reads string safely, preventing buffer overflow, and ensures no garbage characters or newline are left in buffer.
* [ ] Implement `clear_input_buffer()`: flushes the standard input buffer.
* [ ] Implement `to_lowercase(char *str)`: converts input query string to lowercase in place (for case-insensitive searching).
* [ ] Ensure that typing `0` at any input prompt sets the output variable to `0` or returns a cancel code.
