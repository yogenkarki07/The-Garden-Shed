#pragma once
#include "Menu.h"
#include <string>

class CSVmanager {
    std::string dataDirectory;
    std::string menuFile() const;

public:
    explicit CSVmanager(const std::string &dataDirectory = "data");

    bool saveMenu(const Menu& menu) const;
    bool loadMenu(Menu& menu) const;

};