#include <stdio.h>
#include <string.h>

#include "admin.h"

int is_admin_setup_complete(void) { return 0; }

int setup_admin_credentials(const char *username, const char *password) {
  (void)username;
  (void)password;
  return 1;
}

int verify_admin_login(const char *username, const char *password) {
  (void)username;
  (void)password;
  return 0;
}
