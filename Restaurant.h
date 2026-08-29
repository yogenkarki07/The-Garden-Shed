#pragma once
#include "Menu.h"
#include "Table.h"
#include <string>

#include "CSVmanager.h"

class Restaurant {
    Menu menu;
    std::vector<Table> tables;

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

    bool addTable(Table& table); //addTable function
    bool editTable(int number, const Table& replacement); //editTable function
    bool deleteTable(int number); //deleteTable function
    void displayTables(); //displayTables function
};
