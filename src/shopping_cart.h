#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

// Declare cart_count globally
extern int cart_count;
extern double total_price;  // Declare total_price globally to track total price of cart

// Function prototypes
void load_cart(const char *username);
void save_cart();
void add_to_cart(int product_id, int quantity);
void modify_cart_quantity(int product_id, int new_quantity);
void view_cart();
void checkout();

#endif



