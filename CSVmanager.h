#pragma once
#include "Menu.h"
#include "Table.h"
#include <string>

class CSVmanager {
    std::string dataDirectory;
    std::string menuFile() const;
    std::string tableFile() const;

public:
    explicit CSVmanager(const std::string &dataDirectory = "data");

    //Menu
    bool saveMenu(const Menu& menu) const;
    bool loadMenu(Menu& menu) const;

    //Table
    bool saveTable(const std::vector<Table>& tables) const;
    bool loadTable(std::vector<Table>& tables) const;
};