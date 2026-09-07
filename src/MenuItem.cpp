#include "../include/MenuItem.h"
#include <iostream>
#include <string>

//default constructor
MenuItem::MenuItem() : itemId(0), price(0.0), available(true){}

//parameterized constructor
MenuItem::MenuItem(int id, std::string name, std::string category, std::string description, double price, bool available) :
                   itemId(id), name(name), category(category), description(description), price(price), available(available) {}

//getters
int MenuItem::getId() const {
    return itemId;
}

std::string MenuItem::getName() const {
    return name;
}

std::string MenuItem::getCategory() const {
    return category;
}

std::string MenuItem::getDescription() const {
    return description;
}

double MenuItem::getPrice() const {
    return price;
}

bool MenuItem::isAvailable() const {
    return available;
}

//setters

// void MenuItem::setId(const int value) {
//     itemId = value;
// }

void MenuItem::setName(const std::string &value) {
    name = value;
}

void MenuItem::setCategory(const std::string &value) {
    category = value;
}

void MenuItem::setDescription(const std::string &value) {
    description = value;
}

void MenuItem::setPrice(const double value) {
    price = value;
}

void MenuItem::setAvailable(const bool value) {
    available = value;
}