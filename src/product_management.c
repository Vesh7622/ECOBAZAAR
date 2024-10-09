#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "product_management.h"

#define MAX_PRODUCTS 100

Product products[MAX_PRODUCTS];  // Define products as an array of Product structs
int product_count = 0;           // Define product_count

// Load products from file with error handling
void load_products() {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        perror("Error opening products.txt. No products available yet.");
        return; // If file doesn't exist, handle gracefully
    }

    product_count = 0; // Reset product count on load
    while (fscanf(file, "%d %s %lf %d", &products[product_count].id, products[product_count].name, &products[product_count].price, &products[product_count].stock) != EOF) {
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
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        perror("Error opening products.txt for writing.");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        fprintf(file, "%d %s %.2lf %d\n", products[i].id, products[i].name, products[i].price, products[i].stock);
    }

    fclose(file);
}

// Add product to list and save
void add_product(char *name, double price, int stock) {
    products[product_count].id = product_count + 1;
    strcpy(products[product_count].name, name);
    products[product_count].price = price;
    products[product_count].stock = stock;
    product_count++;
    save_products(); // Save products after adding
    printf("Product '%s' added successfully!\n", name);
}

// Sell product (reduce stock) with input validation
void sell_product(int product_id, int quantity) {
    if (product_count == 0) {
        printf("No products available.\n");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        if (products[i].id == product_id) {
            if (products[i].stock < quantity) {
                printf("Insufficient stock for product '%s'. Only %d available.\n", products[i].name, products[i].stock);
                return;
            }
            products[i].stock -= quantity; // Reduce stock
            save_products(); // Save updated stock to file
            printf("Sold %d of '%s'. Stock remaining: %d\n", quantity, products[i].name, products[i].stock);
            return;
        }
    }

    printf("Product not found.\n");
}

// List all products
void list_products() {
    if (product_count == 0) {
      printw("No products available.\n");
      refresh();
      getch();
      endwin();
      return;
    }

    int i = 0;
    mvprintw(0, 5, "ID\tName\tPrice\tStock\n");
    for (i = 0; i < product_count; i++) {
        mvprintw(i + 1, 5, "%d\t%s\t%.2lf\t%d\n", products[i].id, products[i].name, products[i].price, products[i].stock);
    }

    mvprintw(i + 2, 5, "Press any key to go back.");
}

