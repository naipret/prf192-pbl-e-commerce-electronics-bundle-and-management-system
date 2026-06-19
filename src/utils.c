#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    /* Discard characters */
  }
}

int get_safe_int(const char *prompt, int *out_value) {
  char buf[256];
  while (1) {
    printf("%s", prompt);
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
      if (out_value != NULL) {
        *out_value = 0;
      }
      return 0;
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
      clear_input_buffer();
      printf("Invalid entry, please try again.\n");
      continue;
    }

    /* Strip trailing carriage return and newline characters */
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
      buf[len - 1] = '\0';
      len--;
    }

    if (strcmp(buf, "0") == 0) {
      if (out_value != NULL) {
        *out_value = 0;
      }
      return 0; /* Cancel code */
    }

    if (len == 0) {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    char *endptr;
    long val = strtol(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0') {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    if (out_value != NULL) {
      *out_value = (int)val;
    }
    return 1; /* Success */
  }
}

int get_safe_float(const char *prompt, float *out_value) {
  char buf[256];
  while (1) {
    printf("%s", prompt);
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
      if (out_value != NULL) {
        *out_value = 0.0F;
      }
      return 0;
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
      clear_input_buffer();
      printf("Invalid entry, please try again.\n");
      continue;
    }

    /* Strip trailing carriage return and newline characters */
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
      buf[len - 1] = '\0';
      len--;
    }

    if (strcmp(buf, "0") == 0) {
      if (out_value != NULL) {
        *out_value = 0.0F;
      }
      return 0; /* Cancel code */
    }

    if (len == 0) {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    char *endptr;
    double val = strtod(buf, &endptr);
    if (endptr == buf || *endptr != '\0') {
      printf("Invalid entry, please try again.\n");
      continue;
    }

    if (out_value != NULL) {
      *out_value = (float)val;
    }
    return 1; /* Success */
  }
}

void get_safe_string(const char *prompt, char *out_str, int max_len) {
  char buf[1024];
  while (1) {
    printf("%s", prompt);
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
      if (max_len > 0 && out_str != NULL) {
        out_str[0] = '\0';
      }
      return;
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
      clear_input_buffer();
      printf("Input too long. Please try again.\n");
      continue;
    }

    /* Strip trailing carriage return and newline characters */
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
      buf[len - 1] = '\0';
      len--;
    }

    if ((int)len >= max_len) {
      printf("Input too long. Please try again.\n");
      continue;
    }

    if (out_str != NULL) {
      strncpy(out_str, buf, (size_t)(max_len - 1));
      out_str[max_len - 1] = '\0';
    }
    return;
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
