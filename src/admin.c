#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"
#include "utils.h"

static int validate_credential_string(const char *str, int max_len) {
  size_t len = strlen(str);
  if (len < 4 || len >= (size_t)max_len) {
    return 0;
  }
  for (size_t i = 0; i < len; i++) {
    if (isspace((unsigned char)str[i])) {
      return 0;
    }
  }
  return 1;
}

int is_admin_setup_complete(void) {
  FILE *f = fopen("admin.txt", "r");
  if (f != NULL) {
    fclose(f);
    return 1;
  }
  return 0;
}

int setup_admin_credentials(const char *username, const char *password) {
  if (username == NULL || password == NULL) {
    return 0;
  }
  FILE *f = fopen("admin.txt", "w");
  if (f == NULL) {
    return 0;
  }
  fprintf(f, "%s\n", username);
  for (int i = 0; password[i] != '\0'; i++) {
    unsigned char c = (unsigned char)password[i];
    unsigned char obfuscated = (unsigned char)(c ^ 0x5A);
    fprintf(f, "%02X", obfuscated);
  }
  fprintf(f, "\n");
  fclose(f);
  return 1;
}

int verify_admin_login(const char *username, const char *password) {
  if (username == NULL || password == NULL) {
    return 0;
  }
  FILE *f = fopen("admin.txt", "r");
  if (f == NULL) {
    return 0;
  }

  char stored_user[MAX_USERNAME_LEN] = {0};
  char stored_hex[(MAX_PASSWORD_LEN * 2) + 2] = {0};

  if (fgets(stored_user, sizeof(stored_user), f) == NULL) {
    fclose(f);
    return 0;
  }
  size_t user_idx = strcspn(stored_user, "\r\n");
  if (user_idx < sizeof(stored_user)) {
    stored_user[user_idx] = '\0';
  }

  if (fgets(stored_hex, sizeof(stored_hex), f) == NULL) {
    fclose(f);
    return 0;
  }
  size_t hex_idx = strcspn(stored_hex, "\r\n");
  if (hex_idx < sizeof(stored_hex)) {
    stored_hex[hex_idx] = '\0';
  }
  fclose(f);

  if (strcmp(stored_user, username) != 0) {
    return 0;
  }

  /* Obfuscate the input password to compare directly */
  char input_hex[(MAX_PASSWORD_LEN * 2) + 1] = {0};
  size_t input_len = strlen(password);
  if (input_len >= MAX_PASSWORD_LEN) {
    return 0;
  }
  for (size_t i = 0; i < input_len; i++) {
    unsigned char c = (unsigned char)password[i];
    unsigned char obfuscated = (unsigned char)(c ^ 0x5A);
    sprintf(input_hex + (i * 2), "%02X", obfuscated);
  }

  if (strcmp(stored_hex, input_hex) == 0) {
    return 1;
  }
  return 0;
}

void run_admin_registration_wizard(void) {
  char username[128];
  char password[128];

  while (1) {
    get_safe_string("Register Admin Username (0 to cancel): ", username,
                    sizeof(username));
    if (strcmp(username, "0") == 0) {
      printf("Error: Setup is mandatory! You cannot cancel or bypass this "
             "wizard.\n");
      continue;
    }

    if (!validate_credential_string(username, MAX_USERNAME_LEN)) {
      printf("Invalid entry, please try again.\n");
      continue;
    }
    break;
  }

  while (1) {
    get_safe_string("Register Admin Password: ", password, sizeof(password));

    if (!validate_credential_string(password, MAX_PASSWORD_LEN)) {
      printf("Invalid entry, please try again.\n");
      continue;
    }
    break;
  }

  if (setup_admin_credentials(username, password)) {
    printf("Admin registration successful!\n");
  } else {
    printf("Error: Failed to save admin credentials!\n");
  }
}

int run_admin_login_loop(void) {
  char username[128];
  char password[128];
  int attempts = 0;

  while (attempts < 3) {
    get_safe_string("Enter Admin Username (0 to cancel): ", username,
                    sizeof(username));
    if (strcmp(username, "0") == 0) {
      return 0;
    }

    get_safe_string("Enter Admin Password (0 to cancel): ", password,
                    sizeof(password));
    if (strcmp(password, "0") == 0) {
      return 0;
    }

    if (verify_admin_login(username, password)) {
      printf("Login successful!\n");
      return 1;
    }

    attempts++;
    printf("Invalid username or password.\n");
  }

  printf("Too many failed attempts! Returning to Customer Menu.\n");
  return 0;
}
