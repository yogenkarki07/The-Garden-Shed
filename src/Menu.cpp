#include "../include/Menu.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

//getter
const std::vector<MenuItem>& Menu::getItems() const { return items; }

//findItem function  --  read-onlu
const MenuItem* Menu::findItem(int id) const {
    for (const auto& item : items) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

//findItem function  --  modifiable
MenuItem* Menu::findItem(int id) {
    for ( auto& item : items) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

//clear function
void Menu::clear() {
    return items.clear();
}

//addItem function
void Menu::addItem(const MenuItem& item) {
    items.push_back(item);
    std::cout << "Item added successfully ! \n";
}

//editItem Function
bool Menu::editItem(int id, const MenuItem& replacement) {
    MenuItem* item = findItem(id);
    if ( ! item) {
        std::cout << "Item not found ! \n" ;
        return false;
    }
    * item = replacement;
    std::cout << "Item edited successfully ! \n";
    return true;
}

//deleteItem function
bool Menu::deleteItem(int id) {
    auto it = std::find_if(items.begin(), items.end(),
        [id] (const MenuItem& item) {        //lambda function
            return item.getId() == id;                // temporary function to check item through id.
        });

    if (it != items.end()) {
        std::cout << "Item not found ! \n";
        return false;
    }
        items.erase(it);
        std::cout << "Item removed successfully ! \n";
        return true;
}

//displayMenu function
void Menu::displayMenu() const{
    std::cout << "\n==================  Restaurant Menu  =================\n";
    std::cout << std::left << std::setw(5) << "ID"
    << std::setw(24) << "Name" << std::setw(16) << "Category"
    << std::setw(10) << "Price" << "Status" << std::endl;
    std::cout << "\n------------------------------------------------------\n";
    for (const auto& item : items) {
        std::cout << std::left << std::setw(5) << item.getId()
                  << std::setw(24) << item.getName().substr(0, 23)
                  << std::setw(16) << item.getCategory().substr(0, 15)
                  << std::right << std::setw(9) << std::fixed << std::setprecision(2)
                  << item.getPrice() << "  " << (item.isAvailable() ? "Available" : "Unavailable")
                  << std::endl;
    }
    std::cout << "\n======================================================\n";
}
