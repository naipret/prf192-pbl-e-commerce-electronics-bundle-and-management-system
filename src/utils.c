#include <stdio.h>
#include <string.h>

#include "utils.h"

int get_safe_int(const char *prompt, int *out_value) {
  (void)prompt;
  (void)out_value;
  return 0;
}

int get_safe_float(const char *prompt, float *out_value) {
  (void)prompt;
  (void)out_value;
  return 0;
}

void get_safe_string(const char *prompt, char *out_str, int max_len) {
  (void)prompt;
  (void)out_str;
  (void)max_len;
}

void clear_input_buffer(void) {}

void to_lowercase(char *str) { (void)str; }
