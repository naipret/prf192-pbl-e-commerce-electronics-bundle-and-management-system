#include <stdio.h>
#include <string.h>

#include "admin.h"

int is_admin_setup_complete(void) {
  FILE *f = fopen("admin.txt", "rb");
  if (f == NULL) {
    return 0;
  }
  fclose(f);
  return 1;
}

int setup_admin_credentials(const char *username, const char *password) {
  if (username == NULL || password == NULL) {
    return 0;
  }
  FILE *f = fopen("admin.txt", "wb");
  if (f == NULL) {
    return 0;
  }

  /* Obfuscate password with XOR 0x5A */
  char obfuscated_pass[MAX_PASSWORD_LEN] = {0};
  for (int i = 0; i < MAX_PASSWORD_LEN && password[i] != '\0'; i++) {
    obfuscated_pass[i] = (char)(password[i] ^ 0x5A);
  }

  char stored_username[MAX_USERNAME_LEN] = {0};
  strncpy(stored_username, username, MAX_USERNAME_LEN - 1);

  if (fwrite(stored_username, 1, MAX_USERNAME_LEN, f) != MAX_USERNAME_LEN ||
      fwrite(obfuscated_pass, 1, MAX_PASSWORD_LEN, f) != MAX_PASSWORD_LEN) {
    fclose(f);
    return 0;
  }

  fclose(f);
  return 1;
}

int verify_admin_login(const char *username, const char *password) {
  if (username == NULL || password == NULL) {
    return 0;
  }
  FILE *f = fopen("admin.txt", "rb");
  if (f == NULL) {
    return 0;
  }

  char stored_username[MAX_USERNAME_LEN] = {0};
  char stored_pass[MAX_PASSWORD_LEN] = {0};

  if (fread(stored_username, 1, MAX_USERNAME_LEN, f) != MAX_USERNAME_LEN ||
      fread(stored_pass, 1, MAX_PASSWORD_LEN, f) != MAX_PASSWORD_LEN) {
    fclose(f);
    return 0;
  }
  fclose(f);

  if (strcmp(stored_username, username) != 0) {
    return 0;
  }

  char obfuscated_pass[MAX_PASSWORD_LEN] = {0};
  for (int i = 0; i < MAX_PASSWORD_LEN && password[i] != '\0'; i++) {
    obfuscated_pass[i] = (char)(password[i] ^ 0x5A);
  }

  if (memcmp(stored_pass, obfuscated_pass, MAX_PASSWORD_LEN) == 0) {
    return 1;
  }

  return 0;
}
