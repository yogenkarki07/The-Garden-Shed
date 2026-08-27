#pragma once
#include "Menu.h"
#include <string>

#include "CSVmanager.h"

class Restaurant {
    Menu menu;
    CSVmanager csvManager;

    public:
    Restaurant(const std::string& dataDirectory = "data");

    //save and load data function to connect csv files with tables, orders and menu class
    bool saveData() const;
    bool loadData();
};
