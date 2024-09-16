#include <stdio.h>
#include <string.h>
#include "product_management.h"

Product products[MAX_PRODUCTS];
int productCount = 0;

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Product limit reached. Cannot add more products.\n");
        return;
    }
    
    Product newProduct;
    
    printf("Enter product name: ");
    scanf("%s", newProduct.name);
    printf("Enter product price: ");
    scanf("%f", &newProduct.price);
    printf("Enter product quantity: ");
    scanf("%d", &newProduct.quantity);
    
    products[productCount] = newProduct;
    productCount++;
    
    printf("Product added successfully!\n");
}

void updateProduct() {
    // Implementation for updating product
}

void deleteProduct() {
    // Implementation for deleting product
}

void viewProducts() {
    for (int i = 0; i < productCount; i++) {
        printf("%s - $%.2f (Quantity: %d)\n", products[i].name, products[i].price, products[i].quantity);
    }
}

void loadProducts() {
    FILE *file = fopen("products.dat", "rb");
    if (file == NULL) {
        printf("No product data found. Starting fresh.\n");
        return;
    }
    fread(&productCount, sizeof(int), 1, file);
    fread(products, sizeof(Product), productCount, file);
    fclose(file);
}

void saveProducts() {
    FILE *file = fopen("products.dat", "wb");
    fwrite(&productCount, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), productCount, file);
    fclose(file);
}
