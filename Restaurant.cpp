#include "Restaurant.h"
#include<iostream>
#include<string>

Restaurant::Restaurant(const std::string& directory) : csvManager(directory){}

bool Restaurant::saveData() const {
    bool menuSaved = csvManager.saveMenu(menu);
    return menuSaved;
}

bool Restaurant::loadData() {
    bool menuLoaded = csvManager.loadMenu(menu);
    return menuLoaded;
}
