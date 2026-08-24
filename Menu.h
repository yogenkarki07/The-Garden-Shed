#pragma once
#include "MenuItem.h"
#include<string>
#include<vector>

class Menu {
    std::vector <MenuItem> items;

    public:
    const std::vector<MenuItem>& getItems() const;
    //function overloading -- compile-time polymorphism
    const MenuItem* findItem(int itemId) const;   //pointer cannot be modified  - const
    MenuItem* findItem(int itemId);               // pointer can be modified - edit menu

    void addItem (const MenuItem& item);
    bool editItem (int itemId,
        const std::string& name,
        const std::string& category,
        const std::string& description,
        double price,
        bool available);

};


