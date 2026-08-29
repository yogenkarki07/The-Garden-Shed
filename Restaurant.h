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

    //save and load data function to connect csv files with tables, orders and menu class
    bool saveData() const;
    bool loadData();
};
