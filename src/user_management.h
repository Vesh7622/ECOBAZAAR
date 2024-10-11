#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

// Define the User structure
typedef struct {
    char username[50];
    char password[50];
} User;

// Declare users and user_count as extern so other modules can access them
extern User users[];    // Declare users as an array of User structs
extern int user_count;  // Declare user_count

// Function prototypes
void load_users();
void save_users();
int login_user(char *username);  // Login function
int register_user(char *username);  // Register function

#endif

