#include <assert.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

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

static void test_to_lowercase(void) {
  printf("Running test_to_lowercase...\n");
  char str1[] = "Hello World!";
  to_lowercase(str1);
  assert(strcmp(str1, "hello world!") == 0);

  char str2[] = "12345 ABCDE";
  to_lowercase(str2);
  assert(strcmp(str2, "12345 abcde") == 0);

  char str3[] = "";
  to_lowercase(str3);
  assert(strcmp(str3, "") == 0);
  printf("test_to_lowercase passed!\n");
}

static void test_get_safe_string(void) {
  printf("Running test_get_safe_string...\n");

  // Normal string
  set_stdin_input("hello world\n");
  char buf[50];
  get_safe_string("Enter: ", buf, sizeof(buf));
  assert(strcmp(buf, "hello world") == 0);

  // Exceeds buffer length: should truncate and clear the remaining buffer
  // We feed "abcdefg\n" and then "nextline\n"
  set_stdin_input("abcdefg\nnextline\n");
  char small_buf[5];
  get_safe_string("Enter short: ", small_buf, sizeof(small_buf));
  // The small_buf size is 5, so it reads at most 4 chars plus '\0'
  assert(strcmp(small_buf, "abcd") == 0);

  // The next read should get "nextline" because the input buffer was cleared of
  // "efg\n"
  char next_buf[20];
  get_safe_string("Enter next: ", next_buf, sizeof(next_buf));
  assert(strcmp(next_buf, "nextline") == 0);

  printf("test_get_safe_string passed!\n");
}

static void test_get_safe_int(void) {
  printf("Running test_get_safe_int...\n");

  int val = -999;
  int res;

  // Normal valid input
  set_stdin_input("42\n");
  res = get_safe_int("Enter int: ", &val);
  assert(res == 1);
  assert(val == 42);

  // Valid input with spaces
  set_stdin_input("  -123  \n");
  res = get_safe_int("Enter int: ", &val);
  assert(res == 1);
  assert(val == -123);

  // Cancellation (typing 0)
  set_stdin_input("0\n");
  res = get_safe_int("Enter int: ", &val);
  assert(res == 0);
  assert(val == 0);

  // Invalid format first, then valid
  set_stdin_input("abc\n99\n");
  res = get_safe_int("Enter int: ", &val);
  assert(res == 1);
  assert(val == 99);

  // Bounds limit check (INT_MAX check)
  // Let's pass a value that overflows long, then a value that overflows int,
  // then a valid one
  set_stdin_input("9999999999999999999999999999\n2147483648\n2147483647\n");
  res = get_safe_int("Enter int: ", &val);
  assert(res == 1);
  assert(val == INT_MAX);

  // Trailing garbage (should retry)
  set_stdin_input("123abc\n50\n");
  res = get_safe_int("Enter int: ", &val);
  assert(res == 1);
  assert(val == 50);

  printf("test_get_safe_int passed!\n");
}

static void test_get_safe_float(void) {
  printf("Running test_get_safe_float...\n");

  float val = -999.0f;
  int res;

  // Normal valid input
  set_stdin_input("3.14159\n");
  res = get_safe_float("Enter float: ", &val);
  assert(res == 1);
  assert(fabsf(val - 3.14159f) < 0.0001f);

  // Cancellation (typing 0)
  set_stdin_input("0\n");
  res = get_safe_float("Enter float: ", &val);
  assert(res == 0);
  assert(val == 0.0f);

  // Invalid format first, then valid
  set_stdin_input("xyz\n-2.5\n");
  res = get_safe_float("Enter float: ", &val);
  assert(res == 1);
  assert(fabsf(val - (-2.5f)) < 0.0001f);

  // Trailing garbage (should retry)
  set_stdin_input("1.23xyz\n9.81\n");
  res = get_safe_float("Enter float: ", &val);
  assert(res == 1);
  assert(fabsf(val - 9.81f) < 0.0001f);

  printf("test_get_safe_float passed!\n");
}

int main(void) {
  test_to_lowercase();
  test_get_safe_string();
  test_get_safe_int();
  test_get_safe_float();
  printf("All tests completed successfully!\n");
  return 0;
}
