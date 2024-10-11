#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "product_management.h"
#include "shopping_cart.h"

#define MAX_CART_ITEMS 100

typedef struct {
    int product_id;
    int quantity;
} CartItem;

CartItem cart[MAX_CART_ITEMS];
int cart_count = 0;
double total_price = 0.0;  // Running total for the cart
char cart_filename[100];

// Load cart from a file associated with the current user
void load_cart(const char *username) {
    sprintf(cart_filename, "cart_%s.txt", username);
    FILE *file = fopen(cart_filename, "r");

    if (file == NULL) {
        cart_count = 0;
        total_price = 0.0;  // Reset total price
        return;
    }

    cart_count = 0;
    total_price = 0.0;  // Reset total price

    int product_id, quantity;
    while (fscanf(file, "%d %d", &product_id, &quantity) != EOF) {
        cart[cart_count].product_id = product_id;
        cart[cart_count].quantity = quantity;
        cart_count++;

        for (int i = 0; i < product_count; i++) {
            if (products[i].id == product_id) {
                total_price += products[i].price * quantity;  // Calculate total price
                break;
            }
        }
    }

    fclose(file);
}

// Save the current cart to a file
void save_cart() {
    FILE *file = fopen(cart_filename, "w");

    if (file == NULL) {
        mvprintw(5, 5, "Error saving the shopping cart.\n");
        refresh();
        return;
    }

    for (int i = 0; i < cart_count; i++) {
        fprintf(file, "%d %d\n", cart[i].product_id, cart[i].quantity);
    }

    fclose(file);
}

// Add product to cart and update total price
void add_to_cart(int product_id, int quantity) {
    if (quantity <= 0) {
        mvprintw(5, 5, "Error: Quantity must be greater than zero.");
        refresh();
        return;
    }

    for (int i = 0; i < product_count; i++) {
        if (products[i].id == product_id) {
            if (products[i].stock < quantity) {
                mvprintw(5, 5, "Error: Not enough stock available for '%s'. Stock: %d\n", products[i].name, products[i].stock);
                refresh();
                return;
            }

            for (int j = 0; j < cart_count; j++) {
                if (cart[j].product_id == product_id) {
                    cart[j].quantity += quantity;
                    total_price += products[i].price * quantity;  // Update total price
                    save_cart();
                    mvprintw(5, 5, "Updated cart: Added %d more of '%s'. Total: $%.2f\n", quantity, products[i].name, total_price);
                    refresh();
                    return;
                }
            }

            cart[cart_count].product_id = product_id;
            cart[cart_count].quantity = quantity;
            cart_count++;
            total_price += products[i].price * quantity;  // Update total price
            save_cart();
            mvprintw(5, 5, "Added '%s' to cart. Total: $%.2f\n", products[i].name, total_price);
            refresh();
            return;
        }
    }

    mvprintw(5, 5, "Error: Invalid product ID %d. Please try again.\n", product_id);
    refresh();
    getch();
}

// View items in the cart, including the running total
void view_cart() {
    if (cart_count == 0) {
        mvprintw(5, 5, "Your cart is empty.\n");
        refresh();
        getch();
        return;
    }

    mvprintw(2, 5, "Your Cart:");
    mvprintw(3, 5, "Product ID\tQuantity");

    for (int i = 0; i < cart_count; i++) {
        mvprintw(4 + i, 5, "%d\t\t%d", cart[i].product_id, cart[i].quantity);
    }

    mvprintw(6 + cart_count, 5, "Total Price: $%.2f", total_price);
    refresh();
    getch();
}

// Modify the quantity of a product in the cart
void modify_cart_quantity(int product_id, int new_quantity) {
    if (new_quantity <= 0) {
        mvprintw(5, 5, "Error: Quantity must be greater than zero.");
        refresh();
        return;
    }

    for (int i = 0; i < cart_count; i++) {
        if (cart[i].product_id == product_id) {
            for (int j = 0; j < product_count; j++) {
                if (products[j].id == product_id && products[j].stock >= new_quantity) {
                    total_price -= products[j].price * cart[i].quantity;
                    cart[i].quantity = new_quantity;
                    total_price += products[j].price * new_quantity;
                    save_cart();
                    mvprintw(5, 5, "Cart updated: Quantity of product ID %d set to %d. Total: $%.2f\n", product_id, new_quantity, total_price);
                    refresh();
                    getch();
                    return;
                }
            }
            mvprintw(5, 5, "Error: Insufficient stock for product ID %d.\n", product_id);
            refresh();
            getch();
            return;
        }
    }

    mvprintw(5, 5, "Error: Product ID %d not found in cart.\n", product_id);
    refresh();
    getch();
}

// Checkout process: updates stock and clears cart after purchase
void checkout() {
    if (cart_count == 0) {
        mvprintw(5, 5, "Your cart is empty. Nothing to checkout.");
        refresh();
        getch();
        return;
    }

    for (int i = 0; i < cart_count; i++) {
        int product_id = cart[i].product_id;
        int cart_quantity = cart[i].quantity;

        for (int j = 0; j < product_count; j++) {
            if (products[j].id == product_id) {
                if (products[j].stock < cart_quantity) {
                    mvprintw(5, 5, "Error: Insufficient stock for product '%s'.", products[j].name);
                    refresh();
                    getch();
                    return;
                }
            }
        }
    }

    for (int i = 0; i < cart_count; i++) {
        int product_id = cart[i].product_id;
        int cart_quantity = cart[i].quantity;

        for (int j = 0; j < product_count; j++) {
            if (products[j].id == product_id) {
                products[j].stock -= cart_quantity;
            }
        }
    }

    save_products();  // Save updated stock after checkout
    cart_count = 0;
    total_price = 0.0;  // Reset total price after checkout
    save_cart();

    mvprintw(5, 5, "Checkout complete! Your cart has been purchased.");
    refresh();
    getch();
}
