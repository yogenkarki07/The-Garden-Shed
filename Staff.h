#pragma once
#include <iostream>
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
    virtual std::string role() = 0;
    virtual void displayDashboard() = 0;

};

