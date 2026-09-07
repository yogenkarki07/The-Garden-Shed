#pragma once
#include "OrderItem.h"
#include <string>
#include <vector>

enum class orderStatus {
    pending,
    preparing,
    ready,
    served,
    cancelled
};

class Order {
    int orderId;
    int tableNumber;
    std::string customerName;
    std::string specialInstruction;
    orderStatus status;
    std::string orderDateTime;
    std::vector <OrderItem> items;

    public:
    //constructors
    Order();
    Order(int id, int tableNumber, std::string customerName, std::string instruction, std::string dateTime);

    //getters -- to read data
    int getOrderId() const;
    int getTableNumber() const;
    std::string getCustomerName() const;
    std::string getSpecialInstruction() const;
    std::string getOrderDateTime() const;

    orderStatus getStatus() const;
    const std::vector <OrderItem>& getItems() const;  //getItems function - used while read data in files
    std::string getDate() const; //getDate function - used to display previous date orders

    // setters -- to modify data
    void setTableNumber(int value);
    void setCustomerName(std::string value);
    void setSpecialInstruction(std::string value);
    void setOrderDateTime(std::string value);
    void setStatus(orderStatus value);

    // Converts any OrderStatus enum token into its exact written text.
    static std::string statusTostring(orderStatus status);
    //Performs the reverse job; converts raw written text back into OrderStatus enum type. --used in setStatus
    static orderStatus stringToStatus(const std::string& value);
    //function to read converted status -- used everywhere inplace of setStatus/getStatus
    std::string statusString() const;

    //order management functions
    void addItem(const OrderItem& item);
    bool removeItem(int menuItemId);
    bool updateItemQuantity(int menuItemId, int quantity);

    //getTotalOrderPrice - Function to read data(total ordered price)
    double getTotalOrderPrice() const;
    //function to display ordered list
    void displayOrderInfo() const;

};