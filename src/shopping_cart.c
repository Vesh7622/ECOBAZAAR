#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>  // Or <pdcurses.h> for PDCurses
#include "product_management.h"

#define MAX_CART_ITEMS 100

typedef struct {
    int product_id;
    int quantity;
} CartItem;

CartItem cart[MAX_CART_ITEMS];
int cart_count = 0;
char cart_filename[100];

// Load cart from a file associated with the current user
void load_cart(const char *username) {
    sprintf(cart_filename, "cart_%s.txt", username);
    FILE *file = fopen(cart_filename, "r");

    if (file == NULL) {
        cart_count = 0;
        return;
    }

    cart_count = 0;
    while (fscanf(file, "%d %d", &cart[cart_count].product_id, &cart[cart_count].quantity) != EOF) {
        cart_count++;
        if (cart_count >= MAX_CART_ITEMS) {
            mvprintw(5, 5, "Error: Maximum cart limit reached.");
            break;
        }
    }

    fclose(file);
}

// Save the current cart to a file
void save_cart() {
    FILE *file = fopen(cart_filename, "w");

    if (file == NULL) {
        mvprintw(5, 5, "Error saving the shopping cart.");
        refresh();
        return;
    }

    for (int i = 0; i < cart_count; i++) {
        fprintf(file, "%d %d\n", cart[i].product_id, cart[i].quantity);
    }

    fclose(file);
}

// Add product to cart and save it to the file
void add_to_cart(int product_id, int quantity) {
    if (quantity <= 0) {
        mvprintw(5, 5, "Error: Quantity must be greater than zero.");
        refresh();
        return;
    }

    int product_exists = 0;
    for (int i = 0; i < product_count; i++) {
        if (products[i].id == product_id) {
            product_exists = 1;
            if (products[i].stock < quantity) {
                mvprintw(5, 5, "Error: Not enough stock available for '%s'. Stock: %d", products[i].name, products[i].stock);
                refresh();
                return;
            }
            break;
        }
    }

    if (!product_exists) {
        mvprintw(5, 5, "Error: Invalid product ID %d. Please try again.", product_id);
        refresh();
        return;
    }

    for (int i = 0; i < cart_count; i++) {
        if (cart[i].product_id == product_id) {
            cart[i].quantity += quantity;
            save_cart();
            mvprintw(5, 5, "Updated cart: Added %d more of product ID %d", quantity, product_id);
            refresh();
            return;
        }
    }

    cart[cart_count].product_id = product_id;
    cart[cart_count].quantity = quantity;
    cart_count++;
    save_cart();
    mvprintw(5, 5, "Product ID %d added to cart with quantity %d", product_id, quantity);
    refresh();
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
                    cart[i].quantity = new_quantity;
                    save_cart();
                    mvprintw(5, 5, "Cart updated: Quantity of product ID %d set to %d", product_id, new_quantity);
                    refresh();
                    return;
                }
            }
            mvprintw(5, 5, "Error: Insufficient stock for product ID %d.", product_id);
            refresh();
            return;
        }
    }
    mvprintw(5, 5, "Error: Product ID %d not found in cart.", product_id);
    refresh();
}

// View items in the cart
void view_cart() {
    clear();
    if (cart_count == 0) {
        mvprintw(5, 5, "Your cart is empty.");
        refresh();
        getch();
        return;
    }

    mvprintw(2, 5, "Your Cart:");
    mvprintw(3, 5, "Product ID\tQuantity");
    for (int i = 0; i < cart_count; i++) {
        mvprintw(4 + i, 5, "%d\t\t%d", cart[i].product_id, cart[i].quantity);
    }

    refresh();
    getch();
}

// Remove an item from the cart and save the changes
void remove_from_cart(int product_id) {
    for (int i = 0; i < cart_count; i++) {
        if (cart[i].product_id == product_id) {
            for (int j = i; j < cart_count - 1; j++) {
                cart[j] = cart[j + 1];
            }
            cart_count--;
            save_cart();
            mvprintw(5, 5, "Removed product ID %d from cart.", product_id);
            refresh();
            return;
        }
    }
    mvprintw(5, 5, "Product ID %d not found in cart.", product_id);
    refresh();
}

// Checkout process: updates stock and clears cart after purchase
void checkout() {
    clear();
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
                    mvprintw(5, 5, "Error: Insufficient stock for product '%s'. Stock: %d, Cart quantity: %d",
                             products[j].name, products[j].stock, cart_quantity);
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

    save_products();
    cart_count = 0;
    save_cart();

    mvprintw(5, 5, "Checkout complete! Your cart has been purchased.");
    refresh();
    getch();
}




