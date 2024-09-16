#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
    int isSeller; // 1 for seller, 0 for buyer
} User;

extern User users[MAX_USERS];
extern int userCount;
extern User *currentUser;

void registerUser();
int loginUser();
void loadData();
void saveData();

#endif
