🛒 ECOBAZAAR - Online Retail Shop Management System (C Programming)
Welcome to ECOBAZAAR, an online retail shop management system implemented in C. This system allows users to register, log in, and either sell or buy products, featuring a text-based user interface (TUI) using the ncurses library. All product and user data is stored in text files, making it lightweight and easy to manage without a database.

📝 Assignment Requirements
This project was developed as part of the SIS 2075 - Software Engineering 1 course. The goal is to build a simple retail shop system, using version control (Git and GitHub) to manage collaborative development and different versions of the software modules.

📋 Features
👥 User Management
User Registration: Buyers and sellers can register by providing a username and password.
Secure Login: Users log in with their credentials and are directed to either the buyer or seller interface.
🛒 Buyer Features
Browse Products: Buyers can view all available products.
Add to Cart: Buyers can select products by their ID and add them to their shopping cart.
Modify Cart: Update product quantities or remove items from the cart.
Checkout: Buyers can complete their purchase, reducing product stock accordingly.
🛍️ Seller Features
Add Products: Sellers can add new products to the inventory.
Manage Products: Sellers can view and manage their added products, including updating stock and removing products.
🔒 File-Based Data Storage
Persistent Data: User and product data is stored in files, ensuring persistence across sessions.
🚀 Getting Started
Prerequisites
GCC: To compile C programs.
ncurses: Library for creating terminal-based user interfaces.
Install ncurses (on Ubuntu/Debian-based systems):
bash
Copy code
sudo apt-get install libncurses5-dev libncursesw5-dev
Installation
Clone the repository:

bash
Copy code
git clone https://github.com/your-username/online-retail-shop.git
cd online-retail-shop
Compile the project:

bash
Copy code
gcc ui.c product_management.c shopping_cart.c user_management.c -o retail_shop -lncurses
Run the program:

bash
Copy code
./retail_shop
📂 File Structure
ui.c: Manages the user interface (UI) and interactions.
product_management.c: Handles product management functions like adding, listing, and selling products.
shopping_cart.c: Manages shopping cart operations.
user_management.c: Handles user registration and login.
products.txt: Stores product information.
cart_[username].txt: Stores shopping cart information for each user.
📜 Assignment Specifications
Project Guidelines
Modular Design: The project is broken into modules such as user management, product management, shopping cart, and UI.
Own Defined Libraries: Header files (.h) and functions are used throughout the program.
Version Control with Git & GitHub:
Git was used to manage versions and track changes.
GitHub was used as a collaborative platform for sharing code among team members.
Git and GitHub Usage
Branching: Branches were used for each module, e.g., feature/product-management.
Version Control: Changes were committed regularly, allowing rollback to previous versions.
Collaboration: Team members used pull requests and reviewed each other's code on GitHub.
Key Git Commands Used:
git clone: Cloning the repository to start development.
git branch: Creating branches for different modules.
git checkout: Switching between branches during development.
git add, git commit, git push: Adding, committing, and pushing changes to GitHub.
git pull: Merging updates from other team members.
git merge: Merging branches after resolving conflicts.
📂 Example Data (products.txt)
txt
Copy code
1  guitar               3500.00      1
2  refrigerator          5000.00      2
3  washing_machine       4500.00      1
4  wardrobe              6000.00      3
5  Home_Gym              5500.00      2
6  Flush_Door            1000.00      3
7  Television            4000.00      2
8  PlayStation_4        10000.00      1
9  Wooden_Table          8000.00      3
🤝 Contributing
Contributions are welcome! Please fork the repository and submit a pull request for review.


📝 License
This project is licensed under the MIT License.
