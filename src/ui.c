#include <curses.h>
#include <string.h>
#include <stdio.h>
#include "user_management.h"
#include "product_management.h"
#include "shopping_cart.h"
#include <stdlib.h>

extern int cart_count;
extern double total_price;  // Keep track of the total price in the cart
char current_user[50];  // Store current logged-in user

// Function declarations
void initialize_ui();
void finalize_ui();
void logout();
void display_home_menu();
void display_buyer_seller_menu();
void display_buyer_menu();
void display_seller_menu();
void browse_products_screen();
void view_cart_screen();
void login_screen();
void register_screen();
void modify_cart_screen();
void checkout_screen();
void add_product_screen();
void view_added_products_screen();
void sell_product_screen();
void browse_products_and_add_to_cart();

// Initialize PDCurses
void initialize_ui() {
    load_products();
    load_users();
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
}

// Finalize PDCurses
void finalize_ui() {
    endwin();
}

// Logout function that clears the current session
void logout() {
    strcpy(current_user, ""); // Clear the current user
    cart_count = 0;           // Clear the cart
    total_price = 0.0;        // Reset the total price
    clear();
    mvprintw(5, 5, "Logged out successfully.");
    refresh();
    getch();
    display_home_menu(); // Return to the home screen
}

// Home Menu (Login, Register, Exit)
void display_home_menu() {
    char *menu_items[] = {"Login", "Register", "Exit"};
    int choice = 0;
    int ch;

    while (1) {
        clear();

        for (int i = 0; i < 3; i++) {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(2 + i, 5, "%s", menu_items[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        refresh();
        ch = getch();

        switch (ch) {
            case KEY_UP:
                choice--;
                if (choice < 0) choice = 2;
                break;
            case KEY_DOWN:
                choice++;
                if (choice > 2) choice = 0;
                break;
            case 10: // Enter key
                switch (choice) {
                    case 0: login_screen(); break;  // Login
                    case 1: register_screen(); break;  // Register
                    case 2: clear(); refresh(); exit(0);  // Exit
                }
                break;
        }
    }
}

// Buyer or Seller selection menu
void display_buyer_seller_menu() {
    char *menu_items[] = {"Buy", "Sell", "Logout"};
    int choice = 0;
    int ch;

    while (1) {
        clear();
        mvprintw(0, 5, "Would you like to Buy or Sell?");

        for (int i = 0; i < 3; i++) {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(2 + i, 5, "%s", menu_items[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        refresh();
        ch = getch();

        switch (ch) {
            case KEY_UP:
                choice--;
                if (choice < 0) choice = 2;
                break;
            case KEY_DOWN:
                choice++;
                if (choice > 2) choice = 0;
                break;
            case 10: // Enter key
                switch (choice) {
                    case 0: display_buyer_menu(); break;  // Buy
                    case 1: display_seller_menu(); break; // Sell
                    case 2: logout(); return;             // Logout
                }
                break;
        }
    }
}

// Buyer Menu: View Products, View Cart, Modify Cart, Checkout, Logout
void display_buyer_menu() {
    char *menu_items[] = {"Browse Products and Add to Cart", "View Cart", "Modify Cart", "Checkout", "Logout"};
    int choice = 0;
    int ch;

    while (1) {
        clear();
        mvprintw(0, 5, "Total Price: $%.2f", total_price);  // Display current total

        for (int i = 0; i < 5; i++) {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(2 + i, 5, "%s", menu_items[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        refresh();
        ch = getch();

        switch (ch) {
            case KEY_UP:
                choice--;
                if (choice < 0) choice = 4;
                break;
            case KEY_DOWN:
                choice++;
                if (choice > 4) choice = 0;
                break;
            case 10: // Enter key
                switch (choice) {
                    case 0: browse_products_and_add_to_cart(); break;  // Call shopping cart function
                    case 1: view_cart_screen(); break;                 // Call shopping cart function
                    case 2: modify_cart_screen(); break;               // Call shopping cart function
                    case 3: checkout_screen(); break;                  // Call shopping cart function
                    case 4: logout(); return;                          // Logout
                }
                break;
        }
    }
}

// Add Product to Cart
void browse_products_and_add_to_cart() {
    clear();
    browse_products_screen();  // Display the list of products
    refresh();  // Ensure the product list is visible
    getch();    // Wait for the user to view the products before proceeding

    // Now clear the screen and prompt the user for input
    clear();  // Clear the screen for input
    int product_id, quantity;
echo();
    mvprintw(5, 5, "Enter Product ID to add to cart: ");
    scanw("%d", &product_id);
    mvprintw(6, 5, "Enter quantity: ");
    scanw("%d", &quantity);

    add_to_cart(product_id, quantity);  // Call shopping cart function to add product

    mvprintw(8, 5, "Product added to cart. Press any key to return.");
    refresh();
    getch();
    noecho();
}


// View Cart Screen
void view_cart_screen() {
    clear();
    view_cart();  // Call shopping cart function to view cart
    refresh();
    getch();
}

// Modify Cart Screen
void modify_cart_screen() {
    clear();
    int product_id, new_quantity;
    mvprintw(2, 5, "Enter Product ID to modify: ");
    scanw("%d", &product_id);
    mvprintw(3, 5, "Enter new quantity: ");
    scanw("%d", &new_quantity);

    modify_cart_quantity(product_id, new_quantity);  // Call shopping cart function to modify cart
    mvprintw(5, 5, "Cart updated successfully. Press any key to return.");
    refresh();
    getch();
}

// Checkout screen
void checkout_screen() {
    clear();
    checkout();  // Call shopping cart function to handle checkout
    refresh();
    getch();
}

// Seller Menu
void display_seller_menu() {
    char *menu_items[] = {"Add Product", "View Added Products", "Logout"};
    int choice = 0;
    int ch;

    while (1) {
        clear();

        for (int i = 0; i < 3; i++) {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(2 + i, 5, "%s", menu_items[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        refresh();
        ch = getch();

        switch (ch) {
            case KEY_UP:
                choice--;
                if (choice < 0) choice = 2;
                break;
            case KEY_DOWN:
                choice++;
                if (choice > 2) choice = 0;
                break;
            case 10: // Enter key
                switch (choice) {
                    case 0: add_product_screen(); break;       // Add Product
                    case 1: view_added_products_screen(); break;// View Added Products
                    case 2: logout(); return;                  // Logout
                }
                break;
        }
    }
}

// Add Product Screen
void add_product_screen() {
    char product_name[50];
    double product_price;
    int product_stock;

    clear();
    echo();
    mvprintw(2, 5, "Enter Product Name: ");
    getstr(product_name);
    mvprintw(3, 5, "Enter Product Price: ");
    scanw("%lf", &product_price);
    mvprintw(4, 5, "Enter Product Stock: ");
        scanw("%d", &product_stock);
    noecho();

    add_product(product_name, product_price, product_stock);  // Call product management function to add product

    mvprintw(6, 5, "Product added successfully! Press any key to return.");
    refresh();
    getch();
}

// View Added Products Screen
void view_added_products_screen() {
    clear();
    mvprintw(2, 5, "Your added products:");
    list_products();  // Use the product management function to display the list of added products
    refresh();
    getch();
}

// Sell Product Screen
void sell_product_screen() {
    int product_id, quantity;

    clear();
    mvprintw(2, 5, "Enter Product ID to sell: ");
    scanw("%d", &product_id);
    mvprintw(3, 5, "Enter quantity to sell: ");
    scanw("%d", &quantity);

    sell_product(product_id, quantity);  // Call product management function to sell the product

    mvprintw(5, 5, "Product sold successfully! Press any key to return.");
    refresh();
    getch();
}

// Login screen (just call the function from user_management)
void login_screen() {
    clear();
    if (login_user(current_user)) {
        mvprintw(5, 5, "Login Successful! Welcome %s", current_user);
        refresh();
        getch();
        display_buyer_seller_menu();
    } else {
        mvprintw(5, 5, "Login Failed. Please try again.");
        refresh();
        getch();
    }
}

// Register screen (just call the function from user_management)
void register_screen() {
    clear();
    if (register_user(current_user)) {
        mvprintw(5, 5, "User Registered Successfully! Welcome %s", current_user);
    } else {
        mvprintw(5, 5, "Registration Failed. Please try again.");
    }
    refresh();
    getch();
}