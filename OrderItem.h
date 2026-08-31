#pragma once
#include <string>

class OrderItem {
    int menuItemId;
    std::string itemName;
    double itemPrice;
    int itemQuantity;

    public:
    //Constructors
    OrderItem();
    OrderItem(int menuItemId, const std::string& itemName, double itemPrice, int itemQuantity);

    //Getters - to read the values of order-items
    //used const - coz we only read values, not modify
    int getMenuItemId() const;
    std::string getItemName() const;
    double getItemPrice() const;
    int getItemQuantity() const;
    double getTotalItemPrice() const;

    //setters - to modify the values
    void setItemQuantity(int value);
};


