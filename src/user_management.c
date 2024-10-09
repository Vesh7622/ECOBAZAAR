#include <stdio.h>
#include <string.h>
#include "user_management.h"

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
    char role[10]; // 'admin' or 'customer'
} User;

User users[MAX_USERS];
int user_count = 0;

// Load users from file with error handling
void load_users() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        perror("Error opening users.txt. No users available yet.");
        return; // If the file doesn't exist, handle gracefully
    }

    user_count = 0; // Reset user count on load
    while (fscanf(file, "%s %s %s", users[user_count].username, users[user_count].password, users[user_count].role) != EOF) {
        user_count++;
        if (user_count >= MAX_USERS) {
            fprintf(stderr, "Error: Maximum user limit reached.\n");
            break;
        }
    }

    fclose(file);
}

// Save users to file with error handling
void save_users() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        perror("Error opening users.txt for writing.");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].role);
    }

    fclose(file);
}

// Login function with improved error messages
int login_user(char *username, char *password, char *role) {
    if (user_count == 0) {
        printf("No users registered yet. Please register first.\n");
        return 0;
    }

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            strcpy(role, users[i].role); // Set the role
            return 1; // Success
        }
    }

    printf("Invalid username or password.\n");
    return 0; // Failure
}

// Register a user
int register_user(char *username, char *password, char *role) {
    if (strlen(username) == 0 || strlen(password) == 0) {
        printf("Error: Username or password cannot be empty.\n");
        return 0;
    }

    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    strcpy(users[user_count].role, role);
    user_count++;
    save_users(); // Save users after successful registration
    return 1;
}

