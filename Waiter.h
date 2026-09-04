#pragma once
#include "Staff.h"
#include "Restaurant.h"

class Waiter : public Staff {
    public:
    //constructor
    Waiter(int id, std::string name);

    //function-overriding
    std::string role() const override ;
    void displayDashboard(Restaurant& restaurant) override;

};
