#include "Menu.h"
#include <iostream>
#include <string>
#include <algorithm>

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
    std::cout << "Item added successfully ! \n";
}

//editItem Function
bool Menu::editItem(int id, const std::string& name, const std::string& category,
    const std::string& description, double price, bool available) {
    MenuItem* item = findItem(id);
    if ( ! item) {
        std::cout << "Item not found ! \n" ;
        return false;
    }
    item ->setName(name);              //updating menu item
    item ->setCategory(category);
    item ->setDescription(description);
    item ->setPrice(price);
    item ->setAvailable(available);
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
    }else {
        items.erase(it);
        std::cout << "Item deleted successfully ! \n";
        return true;
    }
}

//displayMenu function
void Menu::displayMenu() const{
    std::cout << "\n=============  Restaurant Menu ============\n";
    for (const auto& item : items) {
        std::cout << item.getId() << item.getName() << item.getCategory()
        << item.getDescription() << item.getPrice()
        << (item.isAvailable() ? ("available") : ("unavailable")) << std::endl;
    }
    std::cout << "\n===========================================\n";
}
