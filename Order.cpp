#include "Order.h"
#include <iostream>

//default constructor
Order::Order() : orderId(0), tableNumber(0), status(orderStatus::pending) {}

//parameterized constructor
Order::Order(int id, int tableNumber, std::string customerName, std::string instruction, std::string dateTime)
: orderId(id), tableNumber(tableNumber), customerName(customerName), specialInstruction(instruction),
status(orderStatus::pending), orderDateTime(dateTime) {}

//getters -- functions
int Order::getOrderId() const {
    return orderId;
}

int Order::getTableNumber() const {
    return tableNumber;
}

std::string Order::getCustomerName() const {
    return customerName;
}

std::string Order::getSpecialInstruction() const {
    return specialInstruction;
}

std::string Order::getOrderDateTime() const {
    return orderDateTime;
}

orderStatus Order::getStatus() const {
    return status;
}

//runs entire lists of ordered foods and drinks
const std::vector<OrderItem>& Order::getItems() const {
    return items;
}

//getDate function - extract first 10 characters like date 2026-08-09
std::string Order::getDate() const{
    return orderDateTime.size() >= 10 ? orderDateTime.substr(0, 10) : "";
}

//setters -- to modify data
void Order::setTableNumber(int value) {
    tableNumber = value;
}

void Order::setCustomerName(std::string value) {
    customerName = value;
}

void Order::setSpecialInstruction(std::string value) {
    specialInstruction = value;
}

void Order::setOrderDateTime(std::string value) {
    orderDateTime = value;
}

void Order::setStatus(orderStatus value) {
    status = value;
}

//enum class orderStatus related functions
std::string Order::statusTostring(orderStatus status) {
    switch (status) {
        case orderStatus::pending: return "pending";
        case orderStatus::preparing: return "preparing";
        case orderStatus::ready: return "ready";
        case orderStatus::served: return "served";
        case orderStatus::cancel: return "cancel";
    }
    return "unknown";
}

orderStatus Order::stringToStatus(const std::string& value) {
    if (value == "preparing") {
        return orderStatus::preparing;
    }
    if (value == "ready") {
        return orderStatus::ready;
    }
    if (value == "served") {
        return orderStatus::served;
    }
    if (value == "cancel") {
        return orderStatus::cancel;
    }
    return orderStatus::pending;
}

//statusString function
std::string Order::statusString() const{
    return statusTostring(status);
}

//ordered management functions
void Order::addItem(const OrderItem& item) {
    for (auto& i : items) {
        if (i.getMenuItemId() == item.getMenuItemId()) {
            i.setItemQuantity(i.getItemQuantity() + item.getItemQuantity());
            return;
        }
    }
    items.push_back(item);
    std::cout << "Item added in order list. \n";
}

bool Order::removeItem(int menuItemId) {
    for (auto i = items.begin(); i != items.end(); ++i) {
        if (i->getMenuItemId() == menuItemId) {
            items.erase(i);
            std::cout << "Item removed from order list. \n";
            return true;
        }
    }
    std::cout << "Item not found. \n";
    return false;
}

bool Order::updateItemQuantity(int menuItemId, int quantity) {
    for (auto& i : items) {
        if (i.getMenuItemId() == menuItemId) {
            if (quantity == 0) {
                return removeItem(menuItemId);
            }
            i.setItemQuantity(quantity);
            std::cout << "Item updated in order list. \n";
            return true;
        }
    }
}

void Order::getTotalOrderPrice() const {

}

