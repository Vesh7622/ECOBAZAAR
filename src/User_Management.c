#include <stdio.h>
#include <string.h>
#include "user_management.h"

User users[MAX_USERS];
int userCount = 0;

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    User newUser;
    
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    users[userCount] = newUser;
    userCount++;

    printf("Registration successful!\n");
}

void loadUsers() {
    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) {
        printf("No user data found. Starting fresh.\n");
        return;
    }
    fread(&userCount, sizeof(int), 1, file);
    fread(users, sizeof(User), userCount, file);
    fclose(file);
}

void saveUsers() {
    FILE *file = fopen("users.dat", "wb");
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
}

int loginUser() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return i;  // Returning the index of the logged-in user
        }
    }
    printf("Invalid credentials.\n");
    return -1;
}


