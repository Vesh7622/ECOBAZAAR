#include <stdio.h>
#include "buyer.h"
#include "product_management.h"

void buyerMenu() {
    int choice;

    do {
        printf("Buyer Menu\n");
        printf("1. View Products\n");
        printf("2. Add to Cart\n");
        printf("3. Checkout\n");
        printf("4. Log out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewProducts();
                break;
            case 2:
                addToCart();
                break;
            case 3:
                checkout();
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

void addToCart() {
    // Implementation for adding to cart
}

void checkout() {
    // Implementation for checking out
}