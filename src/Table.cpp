#include "../include/Table.h"
#include <iostream>

//Default constructor
Table::Table() : tableNumber(0), capacity(0), status(tableStatus::available){}

// Parameterized constructor
Table::Table(int number, int capacity, tableStatus status) : tableNumber(number), capacity(capacity), status(status){}

//getters
int Table::getTableNumber() const{
    return tableNumber;
}

int Table::getCapacity() const {
    return capacity;
}

tableStatus Table::getStatus() const {
    return status;
}

std::string Table::getReservationName() const {
    return reservationName;
}

std::string Table::getReservationDateTime() const {
    return reservationDateTime;
}

//setters
void Table::setCapacity(int value) {
    capacity = value;
}

void Table::setStatus(tableStatus value) {
    status = value;
}

//reserve function
void Table::reserveTable(const std::string& name, const std::string& dateTime) {
    reservationName = name;
    reservationDateTime = dateTime;
    status = tableStatus::reserved;
}

//clearReservation function
void Table::clearTableReservation() {
    reservationName.clear();
    reservationDateTime.clear();
    status = tableStatus::available;
}

//freetable & availableTable function
bool Table::availableTable(int guest) {
    return guest > 0 && guest <= capacity && status == tableStatus::available;
}

//occupyTable function
bool Table::occupyTable() {
    if (status == tableStatus::available) {
        status = tableStatus::occupied;
        return true;
    }
    return false;
}

//freeTable function
bool Table::freeTable() {
    if (status == tableStatus::occupied) {
        status = tableStatus::available;
        return true;
    }
    return false;
}

std::string Table::stringStatus() const {
    switch (status) {
        case tableStatus::available : return "available";
        case tableStatus::occupied: return "occupied";
        case tableStatus::reserved: return "reserved";
        }
    return "Unknown";
    }
