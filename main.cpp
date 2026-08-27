#include "MenuItem.h"
#include "Menu.h"

#include<iostream>

int main() {
    char again = 'Y';
    int choice;
    do {
        std::cout << " =============  WELCOME  ============\n";
        std::cout << " =============    TO     ============\n";
        std::cout << " ========== The Garden Shed =========\n";
        std::cout << " 1. Waiter \n";
        std::cout << " 2. Kitchen \n";
        std::cout << " 3. Manager \n";
        std::cout << " 4. Exit \n";
        std::cout << " ====================================\n";
        std::cout << " Choose role: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                std::cout << " Thank you \n";
                exit(0);
            default:
                std::cout << " Invalid choice ! \n";
                break;
        }
    }while (toupper(again) == 'Y');
    return 0;
}