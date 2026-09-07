#pragma once
#include "Restaurant.h"
#include <string>

class Staff {
    protected:
    int staffId;
    std::string name;

    public:
    Staff(int id, const std::string& name);

    virtual ~Staff() = default;

    //getters
    int getId();
    std::string getName();

    //virtual functions
    virtual std::string role() const = 0;
    virtual void displayDashboard(Restaurant& restaurant) = 0;

};

