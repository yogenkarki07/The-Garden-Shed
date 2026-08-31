#include "OrderItem.h"
#include <iostream>
#include <string>

// default constructor
OrderItem::OrderItem() : menuItemId(0), itemPrice(0.0), itemQuantity(0) {}

//paramaterized constructor
OrderItem::OrderItem(int menuItemId, const std::string &itemName, double itemPrice, int itemQuantity) :
menuItemId(menuItemId), itemName(itemName) , itemPrice(itemPrice), itemQuantity(itemQuantity) {}

//Getters - functions
int OrderItem::getMenuItemId() const {
    return menuItemId;
}

std::string OrderItem::getItemName() const{
    return itemName;
}

double OrderItem::getItemPrice() const {
    return itemPrice;
}

int OrderItem::getItemQuantity() const {
    return itemQuantity;
}

double OrderItem::getTotalItemPrice() const {
    return itemPrice * itemQuantity;
}

//Setters - function
void OrderItem::setItemQuantity(int value) {
    itemQuantity = value;
}
