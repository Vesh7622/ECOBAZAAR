#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_management.h"
#include "product_management.h"

// Assuming these functions are already defined in your respective modules.
extern User *currentUser; // Ensure currentUser is accessible globally
void postLoginMenu();
void viewProducts();
void addProduct();
void buyProduct();
void sellProduct();
void mainMenu()
 {
    int choice;
    do {
        printf("\nWelcombuil    e to the Online Retail Shop!\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser(); // Function to register a user
                break;
            case 2:
                if (loginUser()) { // Ensure loginUser returns success/failure
                    printf("\nLogin successful!\n");
                    postLoginMenu(); // Call the function for the next menu
                } else {
                    printf("\nLogin failed! Please try again.\n");
                }
                break;
            case 3:
                printf("\nExiting the system.\n");
                saveData(); // Save any data before exiting
                exit(0);
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } while (choice != 3);
}

// This is the menu you show after login is successful
void postLoginMenu() {
    int option;
    do {
        printf("\n--- Main Menu ---\n");
        printf("1. View Products\n");
        printf("2. Add Product\n");
        printf("3. Buy Product\n");
        printf("4. Sell Product\n");
        printf("5. Logout\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                viewProducts(); // View available products
                break;
            case 2:
                if (currentUser->isSeller) {
                    addProduct(); // Add a new product (only if the user is a seller)
                } else {
                    printf("You do not have permission to add products.\n");
                }
                break;
            case 3:
                buyProduct(); // Buy a product
                break;
            case 4:
                sellProduct(); // Sell a product
                break;
            case 5:
                printf("Logging out...\n");
                currentUser = NULL; // Clear the logged-in user
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 5);
}

int main() {
    loadData(); // Load saved user/product data

    mainMenu(); // Display the first menu

    return 0;
}
