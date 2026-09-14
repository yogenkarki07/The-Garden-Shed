#include "../include/Restaurant.h"
#include "../include/Waiter.h"
#include "../include/Kitchen.h"
#include "../include/Table.h"
#include<filesystem>
#include<iostream>

int main() {

    std::filesystem::create_directories("data");

    Restaurant restaurant("data");
    restaurant.loadData();

    // //Incase if tables are empty, this function will store dummy tables. Table.csv file will not be empty.
    if (restaurant.getTables().empty()) {
        restaurant.addTable(Table(1, 2));
        restaurant.addTable(Table(2, 4));
        restaurant.addTable(Table(3, 4));
        restaurant.addTable(Table(4, 6));
        restaurant.addTable(Table(5, 2));
        restaurant.addTable(Table(6, 2));
        restaurant.addTable(Table(7, 8));
        restaurant.addTable(Table(8, 2));
        restaurant.addTable(Table(9, 4));
        restaurant.addTable(Table(10, 2));
    }

    //Incase menu is empty, this function will store menu even though menu.csv file is empty
    if (restaurant.getMenu().getItems().empty()) {
        restaurant.getMenu().addItem(MenuItem(1, "Teriyaki Chicken", "Mains",
    "Grilled chicken with teriyaki glaze and steamed rice.", 22.50));
        restaurant.getMenu().addItem(MenuItem(2, "Miso Ramen", "Mains",
            "Japanese-style ramen with miso broth and vegetables.", 19.90));
        restaurant.getMenu().addItem(MenuItem(3, "Korean Fried Chicken", "Mains",
            "Crispy chicken with Korean-style spicy sauce.", 24.00));
        restaurant.getMenu().addItem(MenuItem(4, "Vegetable Gyoza", "Starters",
            "Pan-fried vegetable dumplings.", 12.50));
        restaurant.getMenu().addItem(MenuItem(5, "Mango Sticky Rice", "Dessert",
            "Sweet sticky rice, fresh mango and coconut.", 11.00));
        restaurant.getMenu().addItem(MenuItem(6, "Lychee Iced Tea", "Drinks",
            "Refreshing iced tea with lychee.", 6.50));
    }

    restaurant.saveData();

    // Manager manager(1, "Manager");
    Waiter waiter (2, "Front of House");
    Kitchen kitchen(3, "Kitchen Staff");

    char again = 'Y';
    int choice;
    do {
        std::cout << " ========== The Garden Shed =========\n";
        std::cout << " 1. Waiter \n";
        std::cout << " 2. Kitchen \n";
        std::cout << " 3. Manager \n";
        std::cout << " 4. Exit \n";
        std::cout << " ====================================\n";
        std::cout << " Choose role: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid choice ! \n";
        }

        switch (choice) {
            case 1:
                waiter.displayDashboard(restaurant);
                break;
            case 2:
                kitchen.displayDashboard(restaurant);
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