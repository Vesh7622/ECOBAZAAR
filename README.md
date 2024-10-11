#Here is a refined version of the `README.md` file that incorporates all the information you've provided, formatted professionally, and with clear instructions for users and developers:

---

# 🛒 ECOBAZAAR - Online Retail Shop Management System

Welcome to **ECOBAZAAR**, a simple command-line-based retail shop management system implemented in C. This system allows users to register, log in, and either sell or buy products. It features a text-based user interface (TUI) using the `ncurses` library and stores data in files, making it lightweight and easy to manage without a database.

<img src="./ecob.jpg" alt="ECOBAZAAR Logo" width="300"/>

## 📋 Features

### 👥 User Management
- **Secure Registration and Login**: Users can register as either buyers or sellers and securely log in with their credentials.
  
### 🛒 Buyer Features
- **View Available Products**: Buyers can browse through a list of products with detailed information (ID, name, price, and stock).
- **Add to Cart**: Easily add products to the shopping cart by specifying the product ID and quantity.
- **Modify Cart**: Buyers can view and modify the items in their cart (increase, decrease, or remove items).
- **Checkout**: Buyers can complete their purchase, which automatically updates product stock.

### 🛍️ Seller Features
- **Add Products**: Sellers can add new products by providing a name, price, and stock quantity.
- **Manage Inventory**: Sellers can view and manage their added products, including updating stock levels and removing products.

### 📂 File-Based Data Storage
- **Persistence Across Sessions**: All user and product data is stored in text files (`products.txt` for products and `cart_[username].txt` for cart data), ensuring that information persists across sessions.
  
## 🚀 Getting Started

### Prerequisites

- **GCC (GNU Compiler Collection)**: The system must have GCC installed to compile the C files.
- **ncurses Library**: Required for creating the text-based user interface (TUI).
- A text editor or IDE such as **Visual Studio Code** or **vim**.

#### Install `ncurses` on Ubuntu/Debian-based Systems:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/online-retail-shop.git
   cd online-retail-shop
   ```

2. **Compile the project**:
   ```bash
   gcc ui.c product_management.c shopping_cart.c user_management.c -o retail_shop -lncurses
   ```

3. **Run the program**:
   ```bash
   ./retail_shop
   ```

### 📂 File Structure

- **`ui.c`**: Manages the user interface and handles the interaction between the user and the system using `ncurses`.
- **`product_management.c`**: Manages all product-related functionality such as adding products, listing products, and reducing stock.
- **`shopping_cart.c`**: Handles the shopping cart operations for buyers, including adding to the cart, modifying quantities, and checking out.
- **`user_management.c`**: Handles user registration and login, ensuring proper access controls for buyers and sellers.
- **`products.txt`**: Stores product data persistently (ID, name, price, and stock).
- **`cart_[username].txt`**: Stores individual users' shopping cart data, allowing each user to manage their cart independently.

## 🛠️ How to Use

### 👤 Login/Register

- **Buyers and Sellers** can both register or log in to access their respective functionalities.
- If you are a **first-time user**, you will need to register by providing a username and password.

### 🛒 Buyer Mode
1. **View Products**: Browse the available products and see details such as price and available stock.
2. **Add Products to Cart**: Enter the product ID and quantity to add it to your cart.
3. **Modify Cart**: Adjust the quantity of items in your cart or remove items.
4. **Checkout**: Complete the purchase, and the system will reduce the stock accordingly.

### 🛍️ Seller Mode
1. **Add New Products**: Enter product details (name, price, and stock) to add new products to the shop.
2. **View and Manage Products**: See a list of your added products, and update or manage the stock.

### Example `products.txt` File

```txt
1  guitar               3500.00      1
2  refrigerator          5000.00      2
3  washing_machine       4500.00      1
4  wardrobe              6000.00      3
5  Home_Gym              5500.00      2
6  Flush_Door            1000.00      3
7  Television            4000.00      2
8  PlayStation_4        10000.00      1
9  Wooden_Table          8000.00      3
```

## 📂 Data Files

- **`products.txt`**: Stores the product information, including product ID, name, price, and stock.
- **`cart_[username].txt`**: Each user has a dedicated cart file (`cart_username.txt`) that stores their cart's state. When a user logs back in, their cart is restored from this file.

## 👨‍💻 Contributing

Contributions are welcome! If you would like to contribute to this project, feel free to fork the repository and create a pull request.

### Steps to Contribute:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature/my-feature`).
3. Make your changes.
4. Commit your changes (`git commit -am 'Add my feature'`).
5. Push to the branch (`git push origin feature/my-feature`).
6. Create a new pull request.

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Let me know if you need any additional customization or further refinements for your `README.md`! This document provides a comprehensive overview of your project and instructions for usage, contributing, and installation.