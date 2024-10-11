#include <stdio.h>
#include <string.h>
#include "product_management.h"
#include <curses.h>

#define MAX_PRODUCTS 100

Product products[MAX_PRODUCTS];  // Define products as an array of Product structs
int product_count = 0;           // Define product_count

// Load products from file with error handling
void load_products() {
    FILE *file = fopen("products.txt", "r");  // Open the file in read mode
    if (file == NULL) {
        perror("Error opening products.txt for reading.");
        return;  // If file doesn't exist, return without loading
    }

    product_count = 0;  // Reset product count before loading products
    while (fscanf(file, "%d %s %lf %d", &products[product_count].id, products[product_count].name, 
                  &products[product_count].price, &products[product_count].stock) != EOF) {
        product_count++;
        if (product_count >= MAX_PRODUCTS) {
            fprintf(stderr, "Error: Maximum product limit reached.\n");
            break;
        }
    }

    fclose(file);
}

// Save products to file with error handling
void save_products() {
    FILE *file = fopen("products.txt", "w");  // Open the file in write mode (overwrite existing)
    if (file == NULL) {
        perror("Error opening products.txt for writing.");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        // Format the output to align the columns with specific widths
        fprintf(file, "%2d %-20s %10.2lf %5d\n", products[i].id, products[i].name, products[i].price, products[i].stock);
    }

    fclose(file);  // Close the file after saving
}

// Add product to list and save
void add_product(char *name, double price, int stock) {
    products[product_count].id = product_count + 1;  // Auto-increment product ID
    strcpy(products[product_count].name, name);
    products[product_count].price = price;
    products[product_count].stock = stock;
    product_count++;
    save_products();  // Save products after adding
    mvprintw(5, 5, "Product '%s' added successfully!", name);  // Display success message
    refresh();
    getch();
}

// Sell product (reduce stock) with input validation
void sell_product(int product_id, int quantity) {
    if (product_count == 0) {
        mvprintw(5, 5, "No products available.");
        refresh();
        getch();
        return;
    }

    for (int i = 0; i < product_count; i++) {
        if (products[i].id == product_id) {
            if (products[i].stock < quantity) {
                mvprintw(5, 5, "Insufficient stock for product '%s'. Only %d available.", products[i].name, products[i].stock);
                refresh();
                getch();
                return;
            }
            products[i].stock -= quantity;  // Reduce stock
            save_products();  // Save updated stock to file
            mvprintw(5, 5, "Sold %d of '%s'. Stock remaining: %d", quantity, products[i].name, products[i].stock);
            refresh();
            getch();
            return;
        }
    }

    mvprintw(5, 5, "Product not found.");
    refresh();
    getch();
}

// List all products
void list_products() {
    if (product_count == 0) {
        mvprintw(5, 5, "No products available.");
        refresh();
        getch();
        return;
    }

    // Properly format the header
    mvprintw(2, 5, "ID  %-20s  %-10s  %-5s", "Name", "Price", "Stock");

    // Display each product with proper spacing
    for (int i = 0; i < product_count; i++) {
        mvprintw(3 + i, 5, "%2d  %-20s  %10.2lf  %5d", 
            products[i].id, products[i].name, products[i].price, products[i].stock);
    }

    refresh();
    getch();  // Wait for user input before returning to the previous screen
}


// Browse Products Screen
void browse_products_screen() {
    clear();  // Clears the screen using curses
    list_products();  // Display the list of products using the list_products function
}

