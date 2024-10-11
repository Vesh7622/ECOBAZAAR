#ifndef PRODUCT_MANAGEMENT_H
#define PRODUCT_MANAGEMENT_H

// Define the Product structure
typedef struct {
    int id;
    char name[50];
    double price;
    int stock;
} Product;

// Declare products and product_count as extern so other modules can access them
extern Product products[];    // Declare products as an array of Product structs
extern int product_count;     // Declare product_count

// Function prototypes
void load_products();
void save_products();
void add_product(char *name, double price, int stock);
void sell_product(int product_id, int quantity);
void list_products();
void browse_products_screen();  // Add the declaration for browse_products_screen
#endif

