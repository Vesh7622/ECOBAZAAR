#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

// Declare cart_count globally
extern int cart_count;

void load_cart(const char *username);
void save_cart();
void add_to_cart(int product_id, int quantity);
void modify_cart_quantity(int product_id, int new_quantity);
void remove_from_cart(int product_id);
void view_cart();
void checkout();

#endif


