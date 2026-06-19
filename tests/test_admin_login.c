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

static void setup_test_credentials(void) {
  unlink("admin.txt");
  int setup_res = setup_admin_credentials("admin", "password123");
  assert(setup_res == 1);
}

static void test_verify_admin_login(void) {
  printf("Running test_verify_admin_login...\n");
  setup_test_credentials();

  assert(verify_admin_login("admin", "password123") == 1);
  assert(verify_admin_login("admin", "wrongpassword") == 0);
  assert(verify_admin_login("wronguser", "password123") == 0);
}

static void test_login_loop_success_first_try(void) {
  printf("Running test_login_loop_success_first_try...\n");
  setup_test_credentials();

  set_stdin_input("admin\npassword123\n");
  int result = run_admin_login_loop();
  assert(result == 1);
}

static void test_login_loop_cancel_username(void) {
  printf("Running test_login_loop_cancel_username...\n");
  setup_test_credentials();

  set_stdin_input("0\n");
  int result = run_admin_login_loop();
  assert(result == 0);
}

static void test_login_loop_cancel_password(void) {
  printf("Running test_login_loop_cancel_password...\n");
  setup_test_credentials();

  set_stdin_input("admin\n0\n");
  int result = run_admin_login_loop();
  assert(result == 0);
}

static void test_login_loop_retries_then_success(void) {
  printf("Running test_login_loop_retries_then_success...\n");
  setup_test_credentials();

  // 1st attempt: wrong user
  // 2nd attempt: wrong password
  // 3rd attempt: correct login
  set_stdin_input("wrong\npassword123\nadmin\nwrong\nadmin\npassword123\n");
  int result = run_admin_login_loop();
  assert(result == 1);
}

static void test_login_loop_lockout(void) {
  printf("Running test_login_loop_lockout...\n");
  setup_test_credentials();

  // 3 wrong attempts
  set_stdin_input("admin\nwrong1\nadmin\nwrong2\nadmin\nwrong3\n");
  int result = run_admin_login_loop();
  assert(result == 0);
}

int main(void) {
  test_verify_admin_login();
  test_login_loop_success_first_try();
  test_login_loop_cancel_username();
  test_login_loop_cancel_password();
  test_login_loop_retries_then_success();
  test_login_loop_lockout();
  clean_files();
  printf("All admin login tests completed successfully!\n");
  return 0;
}
