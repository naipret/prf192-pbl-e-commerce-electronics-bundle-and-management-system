#ifndef ADMIN_H
#define ADMIN_H

#include "types.h"

int is_admin_setup_complete(void);
int setup_admin_credentials(const char *username, const char *password);
int verify_admin_login(const char *username, const char *password);
void run_admin_registration_wizard(void);
int run_admin_login_loop(void);

#endif /* ADMIN_H */
