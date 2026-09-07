#pragma once
#include "Menu.h"
#include "Table.h"
#include "Order.h"
#include <string>

#include "CSVmanager.h"

class Restaurant {
    Menu menu;
    std::vector<Table> tables;
    std::vector<Order> orders;

    CSVmanager csvManager;

    public:
    Restaurant(const std::string& dataDirectory = "data");

    //save and load data functions to connect csv files with tables, orders and menu class
    bool saveData() const;
    bool loadData();

    //Menu operation
    Menu& getMenu();
    const Menu& getMenu() const;

    //Table operations
    Table* findTable(int number);  //findTable function
    const std::vector<Table>& getTables() const;   //getTables function
    //table management
    bool addTable(Table& table); //addTable function
    bool editTable(int number, const Table& replacement); //editTable function
    bool deleteTable(int number); //deleteTable function
    void displayTables(); //displayTables function

    //Table reservations
    void markTableAsOccupied(int tableNumber);
    void markTableAsAvailable(int tableNumber);

    //Order operations
    Order* findOrder(int id);   //findOrder Function
    const std::vector<Order>& getOrders() const;  //getOrders function
    //order management
    int nextOrderId() const;
    bool addOrder(const Order& order); //addOrder function
    bool editOrder(int id, const Order& replacement);  //editOrder function
    bool deleteOrder(int id); //deleteOrder function
    void displayAllOrders(const std::string& date = "") const;  //displayOrders function
};
