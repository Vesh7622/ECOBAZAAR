#include <stdio.h>
#include "ui.h"
#include "user_management.h"
#include "product_management.h"
#include "shopping_cart.h"

int main() {
    // Initialize the user interface with pdcurses
    initialize_ui();

    // Show the main menu to the user
    display_home_menu();

    // Finalize the user interface when done
    finalize_ui();

    return 0;
}

