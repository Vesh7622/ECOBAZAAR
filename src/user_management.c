#include <stdio.h>
#include <string.h>
#include "user_management.h"
#include <curses.h>
#define MAX_USERS 100

User users[MAX_USERS];  // Define the global users array here
int user_count = 0;     // Define the global user count

// Load users from file
void load_users() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        perror("Error opening users.txt. No users available yet.");
        return;
    }

    user_count = 0; // Reset user count on load
    while (fscanf(file, "%s %s", users[user_count].username, users[user_count].password) != EOF) {
        user_count++;
        if (user_count >= MAX_USERS) {
            fprintf(stderr, "Error: Maximum user limit reached.\n");
            break;
        }
    }

    fclose(file);
}

// Save users to file
void save_users() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        perror("Error opening users.txt for writing.");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

// Login user function
int login_user(char *username) {
    char password[50];
    mvprintw(2, 5, "Enter Username: ");
    echo();
    getstr(username);
    mvprintw(3, 5, "Enter Password: ");
    getstr(password);
    noecho();

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;  // Success
        }
    }

    return 0;  // Failure
}

// Register user function
int register_user(char *username) {
    char password[50];

    mvprintw(2, 5, "Enter Username: ");
    echo();
    getstr(username);
    mvprintw(3, 5, "Enter Password: ");
    getstr(password);
    noecho();

    // Check for duplicate username
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            mvprintw(5, 5, "Error: Username already exists.");
            refresh();
            getch();
            return 0;
        }
    }

    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    user_count++;
    save_users();  // Save the users after registration
    return 1;
}
