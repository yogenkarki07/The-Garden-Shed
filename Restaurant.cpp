#include "Restaurant.h"
#include<iostream>
#include<string>

Restaurant::Restaurant(const std::string& directory) : csvManager(directory){}

//saveData function
bool Restaurant::saveData() const {
    bool menuSaved = csvManager.saveMenu(menu);
    bool tableSaved = csvManager.saveTable(tables);
    return menuSaved && tableSaved;
}

//loadData function
bool Restaurant::loadData() {
    bool menuLoaded = csvManager.loadMenu(menu);
    bool tableLoaded = csvManager.loadTable(tables);
    return menuLoaded && tableLoaded;
}
