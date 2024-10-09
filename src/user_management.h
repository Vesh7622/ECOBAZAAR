#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

void load_users();
void save_users();
int login_user(char *username, char *password, char *role);
int register_user(char *username, char *password, char *role);

#endif

