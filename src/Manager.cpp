#include "../include/Restaurant.h"
#include "../include/Manager.h"
#include<iostream>
#include<string>

//static functions to avoid objects
static int mInt(std::string prompt) {
    int value;
    while(true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid Number !\n";
    }
}

static double mDouble(std::string prompt) {
    double value;
    while(true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid / Negative Amount!\n";
    }
}

static std::string mLine(std::string prompt) {
    std::cout << prompt;
    std::cin.ignore(1000, '\n');
    std::string value;
    std::getline(std::cin, value);
    return value;
}

Manager::Manager(int id, std::string name) : Staff(id, name) {}

std::string Manager::role() const {
    return "Manager";
}

void Manager::displayDashboard(Restaurant& restaurant) {
    std::cout << " ================   MANAGER DASHBOARD   ============= \n";
    while (true) {
        std::cout << " 1. Menu Management \n" <<
                     " 2. Table Management \n" <<
                     " 3. Order Management \n" <<
                     " 4. Daily Report \n" <<
                     " 5. Exit \n" ;
        int choice = mInt("Enter Choice");
        switch (choice) {
            case 1:
                return;
            case 2:
                return;
            case 3:
                return;
            case 4:
                return;
            case 5:
                return;
            default:
                std::cout << "Invalid Choice!\n";
                return;
        }
    }

}

