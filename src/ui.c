#include <curses.h>
#include <string.h>
#include <stdio.h>           // Added for standard input/output functions
#include "user_management.h" // Ensure proper declarations for user management functions
#include "product_management.h" // Ensure proper declarations for product management functions
#include "shopping_cart.h"   // Ensure proper declarations for shopping cart functions
#include <stdlib.h>
// cart_count is now accessible globally
extern int cart_count;

char current_user[50];
char current_role[10];

// Function declarations
void initialize_ui();
void finalize_ui();
void logout();
void display_home_menu();
void display_buyer_menu();
void display_seller_menu();
void browse_products_screen();
void view_cart_screen();
void login_screen();
void register_screen();
void modify_cart_screen();
void checkout_screen();
void add_product_screen();  // Declaration for adding a product screen
void sell_product_screen(); // Declaration for selling a product screen


// Initialize PDCurses
void initialize_ui() {
    
    load_products();
    load_users();
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
}

// Finalize PDCurses
void finalize_ui() {
    endwin();
}

// Logout function that clears the current session
void logout() {
    strcpy(current_user, ""); // Clear the current user
    strcpy(current_role, ""); // Clear the role
    cart_count = 0;           // Clear the cart
    clear();
    mvprintw(5, 5, "Logged out successfully.");
    refresh();
    getch();
    display_home_menu(); // Return to the home screen
}

// Home Menu (Login, Register, Exit)
void display_home_menu() {
    char *menu_items[] = {
        "Login",
        "Register",
        "Exit"
    };

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
                    case 0: login_screen(); break; // Login
                    case 1: register_screen(); break; // Register
                    case 2: clear(); refresh(); exit(0);// Exit
                }
                break;
        }
    }
}

// Buyer Menu (with Checkout and Cart Management)
void display_buyer_menu() {
    char *menu_items[] = {
        "Browse Products",
        "View Cart",
        "Modify Cart",
        "Checkout",
        "Logout"
    };

    int choice = 0;
    int ch;

    while (1) {
        clear();

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
                    case 0: browse_products_screen(); break; // Browse Products
                    case 1: view_cart_screen(); break;       // View Cart
                    case 2: modify_cart_screen(); break;     // Modify Cart
                    case 3: checkout_screen(); break;        // Checkout
                    case 4: logout(); return;                // Logout
                }
                break;
        }
    }
}



// Browse Products Screen (correct definition)
void browse_products_screen() {
    clear();
    list_products();  // Use the product management function to list products
    refresh();
    getch();
}

// View Cart Screen (correct definition)
void view_cart_screen() {
    clear();
    view_cart();      // Use the shopping cart function to view cart contents
    refresh();
    getch();
}

// Login screen
void login_screen() {
    char username[50], password[50], role[10];

    clear();
    mvprintw(2, 5, "Enter Username: ");
    echo();
    getstr(username);
    noecho();
    mvprintw(3, 5, "Enter Password: ");
    echo();
    getstr(password);
    noecho();

    if (login_user(username, password, role)) {
        strcpy(current_user, username);
        strcpy(current_role, role);
        mvprintw(5, 5, "Login Successful! Role: %s", role);
        refresh();
        getch();

        if (strcmp(current_role, "admin") == 0) {
            display_seller_menu();
        } else {
            display_buyer_menu();
        }
    } else {
        mvprintw(5, 5, "Login Failed. Please try again.");
        refresh();
        getch();
    }
}

// Register screen
void register_screen() {
    char username[50], password[50], role[10];

    clear();
    mvprintw(2, 5, "Enter Username: ");
    echo();
    getstr(username);
    noecho();
    mvprintw(3, 5, "Enter Password: ");
    echo();
    getstr(password);
    noecho();
    mvprintw(4, 5, "Enter Role (admin/customer): ");
    echo();
    getstr(role);
    noecho();

    if (register_user(username, password, role)) {
        mvprintw(6, 5, "User Registered Successfully!");
    } else {
        mvprintw(6, 5, "Registration Failed. Please try again.");
    }

    refresh();
    getch();
}

// Modify Cart Screen (to update quantities)
void modify_cart_screen() {
    int product_id, new_quantity;
    echo();
    clear();
    mvprintw(2, 5, "Enter Product ID to modify: ");
    scanw("%d", &product_id);
    mvprintw(3, 5, "Enter new quantity: ");
    scanw("%d", &new_quantity);
    noecho();
    modify_cart_quantity(product_id, new_quantity);
    getch();
}

// Checkout screen
void checkout_screen() {
    checkout();
    getch();
}

// Seller Menu (with Logout option)
void display_seller_menu() {
    char *menu_items[] = {
        "View Products",
        "Add Product",
        "Sell Product",
        "Logout"
    };

    int choice = 0;
    int ch;

    while (1) {
        clear();

        for (int i = 0; i < 4; i++) {
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
                if (choice < 0) choice = 3;
                break;
            case KEY_DOWN:
                choice++;
                if (choice > 3) choice = 0;
                break;
            case 10: // Enter key
                switch (choice) {
                    case 0: browse_products_screen(); break; // View Products
                    case 1: add_product_screen(); break;     // Add Product
                    case 2: sell_product_screen(); break;    // Sell Product
                    case 3: logout(); return;                // Logout
                }
                break;
        }
    }
}

// Function to display a screen for adding a product
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
    // Add the product using the product management function
    add_product(product_name, product_price, product_stock);

    mvprintw(6, 5, "Product added successfully!");
    refresh();
    getch();
}

// Function to display a screen for selling a product
void sell_product_screen() {
    int product_id, quantity;

    clear();
    mvprintw(2, 5, "Enter Product ID to sell: ");
    scanw("%d", &product_id);
    mvprintw(3, 5, "Enter quantity to sell: ");
    scanw("%d", &quantity);

    // Sell the product using the product management function
    sell_product(product_id, quantity);

    mvprintw(5, 5, "Product sold successfully!");
    refresh();
    getch();
}