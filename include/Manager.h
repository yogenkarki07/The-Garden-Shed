#pragma once
#include "Staff.h"

class Manager : public Staff{
    public:
    Manager(int id, std::string name);
    std::string role() const override;
    void displayDashboard(Restaurant& restaurant) override;

    private:
    void menuManagement(Restaurant& restaurant);
    void tableManagement(Restaurant& restaurant);
    void orderManagement(Restaurant& restaurant);
    void dailySalesReport(Restaurant& restaurant);
};
