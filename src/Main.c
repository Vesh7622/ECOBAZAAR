#include <stdio.h>
#include <stdlib.h>
#include "user_management.h"
#include "buyer.h"
#include "seller.h"
#include "data_management.h"
int main() {
    int choice;
    
    // Load data from files
    loadData();

    do {
        printf("Welcome to the Online Retail Shop!\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser() == 1) {
                    // After login, check if the user is a buyer or seller
                    if (currentUser->isSeller) {
                        sellerMenu();
                    } else {
                        buyerMenu();
                    }
                }
                break;
            case 3:
                printf("Thank you for visiting the Online Retail Shop!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    // Save data back to files
    saveData();

    return 0;
}