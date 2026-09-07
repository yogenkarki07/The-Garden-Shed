#include "../include/Staff.h"
#include <iostream>
#include <string>

Staff::Staff(int id, const std::string& name) : staffId(id), name(name) {}

//getters -- to read value
int Staff::getId() {
    return staffId;
}

std::string Staff::getName() {
    return name;
}