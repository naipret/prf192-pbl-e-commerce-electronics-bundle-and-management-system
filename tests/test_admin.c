#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "admin.h"

static void set_stdin_input(const char *input) {
  FILE *f = fopen("test_input.txt", "w");
  if (!f) {
    perror("Failed to open test_input.txt");
    return;
  }
  fputs(input, f);
  fclose(f);
  if (!freopen("test_input.txt", "r", stdin)) {
    perror("Failed to redirect stdin");
  }
}

static void clean_files(void) {
  unlink("admin.txt");
  unlink("test_input.txt");
}

static void test_setup_and_login_validation(void) {
  printf("Running test_setup_and_login_validation...\n");
  clean_files();

  // Initially setup should not be complete
  assert(is_admin_setup_complete() == 0);

  // Setup credentials
  int setup_res = setup_admin_credentials("superuser", "securepwd123");
  assert(setup_res == 1);

  // Now setup should be complete
  assert(is_admin_setup_complete() == 1);

  // Verify login matching
  assert(verify_admin_login("superuser", "securepwd123") == 1);

  // Verify failure cases
  assert(verify_admin_login("superuser", "wrongpwd") == 0);
  assert(verify_admin_login("wronguser", "securepwd123") == 0);
  assert(verify_admin_login("superuser", "") == 0);

  // Verify password obfuscation in admin.txt (not plain text)
  FILE *f = fopen("admin.txt", "r");
  assert(f != NULL);
  char line1[100] = {0};
  char line2[100] = {0};
  fgets(line1, sizeof(line1), f);
  fgets(line2, sizeof(line2), f);
  fclose(f);

  line1[strcspn(line1, "\r\n")] = '\0';
  line2[strcspn(line2, "\r\n")] = '\0';

  // Username is plain text
  assert(strcmp(line1, "superuser") == 0);
  // Password must NOT be "securepwd123"
  assert(strcmp(line2, "securepwd123") != 0);

  // Re-verify that it matches hex-encoded XOR
  // securepwd123 obfuscated with 0x5A is:
  // s(0x73)^0x5A = 0x29 -> '29'
  // e(0x65)^0x5A = 0x3F -> '3F'
  // c(0x63)^0x5A = 0x39 -> '39'
  assert(strncmp(line2, "293F39", 6) == 0);

  printf("test_setup_and_login_validation passed!\n");
}

static void test_registration_wizard(void) {
  printf("Running test_registration_wizard...\n");
  clean_files();

  // Test setup with multiple invalid entries:
  // 1. "0" at username prompt (should warning & loop)
  // 2. "usr" at username prompt (too short)
  // 3. "user name" at username (has spaces)
  // 4. "admin" (valid username!)
  // 5. "pwd" at password prompt (too short)
  // 6. "pwd space" at password (has spaces)
  // 7. "goodpassword" (valid password!)
  set_stdin_input("0\nusr\nuser name\nadmin\npwd\npwd space\ngoodpassword\n");

  run_admin_registration_wizard();

  // Setup must be complete and logins matching
  assert(is_admin_setup_complete() == 1);
  assert(verify_admin_login("admin", "goodpassword") == 1);

  printf("test_registration_wizard passed!\n");
}

int main(void) {
  test_setup_and_login_validation();
  test_registration_wizard();
  clean_files();
  printf("All admin tests completed successfully!\n");
  return 0;
}
