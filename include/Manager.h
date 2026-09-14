#pragma once
#include "Staff.h"

class Manager : public Staff{
    public:
    Manager(int id, std::string name);
    std::string role() const override;
    void displayDashboard(Restaurant& restaurant) override;
};
