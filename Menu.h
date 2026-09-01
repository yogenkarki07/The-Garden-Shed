#pragma once
#include "MenuItem.h"
#include<string>
#include<vector>

class Menu {
    std::vector <MenuItem> items;

    public:
    const std::vector<MenuItem>& getItems() const;
    //function overloading -- compile-time polymorphism
    const MenuItem* findItem(int id) const;   //pointer cannot be modified  - const
    MenuItem* findItem(int id);               // pointer can be modified - edit menu

    void clear();
    //Menu management functions
    void addItem (const MenuItem& item);
    bool editItem (int id, const MenuItem& replacement);
    bool deleteItem (int id);
    void displayMenu() const;
};


