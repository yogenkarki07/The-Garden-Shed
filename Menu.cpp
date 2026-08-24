#include "Menu.h"
#include <iostream>
#include <string>

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

//addItem function
void Menu::addItem(const MenuItem& item) {
    items.push_back(item);
}

//editItem Function
bool Menu::editItem(int id, const std::string& name, const std::string& category,
    const std::string& description, double price, bool available) {
    MenuItem* item = findItem(id);
    if ( ! item) {
        std::cout << "Item not found ! \n" ;
        return false;
    }
    item ->setName(name);
    item ->setCategory(category);
    item ->setDescription(description);
    item ->setPrice(price);
    return true;
}