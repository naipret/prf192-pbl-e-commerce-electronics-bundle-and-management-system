#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    /* discard */
  }
}

void to_lowercase(char *str) {
  if (str == NULL) {
    return;
  }
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = (char)tolower((unsigned char)str[i]);
  }
}

void get_safe_string(const char *prompt, char *out_str, int max_len) {
  if (out_str == NULL || max_len <= 0) {
    return;
  }
  if (prompt != NULL) {
    printf("%s", prompt);
    fflush(stdout);
  }
  if (fgets(out_str, max_len, stdin) == NULL) {
    out_str[0] = '\0';
    return;
  }
  size_t len = strlen(out_str);
  if (len > 0 && out_str[len - 1] == '\n') {
    out_str[len - 1] = '\0';
  } else {
    clear_input_buffer();
  }
}

int get_safe_int(const char *prompt, int *out_value) {
  char buf[128];
  while (1) {
    get_safe_string(prompt, buf, sizeof(buf));

    if (strcmp(buf, "0") == 0) {
      if (out_value != NULL) {
        *out_value = 0;
      }
      return 0;
    }

    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);

    if (endptr == buf) {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
      endptr++;
    }
    if (*endptr != '\0') {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    if (out_value != NULL) {
      *out_value = (int)val;
    }
    return 1;
  }
}

int get_safe_float(const char *prompt, float *out_value) {
  char buf[128];
  while (1) {
    get_safe_string(prompt, buf, sizeof(buf));

    if (strcmp(buf, "0") == 0) {
      if (out_value != NULL) {
        *out_value = 0.0F;
      }
      return 0;
    }

    char *endptr;
    errno = 0;
    double val = strtod(buf, &endptr);

    if (endptr == buf) {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
      endptr++;
    }
    if (*endptr != '\0') {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    if (errno == ERANGE) {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    if (out_value != NULL) {
      *out_value = (float)val;
    }
    return 1;
  }
}
