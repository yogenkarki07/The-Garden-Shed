#pragma once
#include "Staff.h"

class Kitchen : public Staff {
    public:
    Kitchen(int id, std::string name);
    std::string role() const override ;
    void displayDashboard(Restaurant& restaurant) override ;
};
