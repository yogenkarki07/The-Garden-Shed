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
void Table::reserve(const std::string& name, const std::string& dateTime) {
    reservationName = name;
    reservationDateTime = dateTime;
    status = tableStatus::reserved;
}

//clearReservation function
void Table::clearReservation() {
    reservationName.clear();
    reservationDateTime.clear();
    status = tableStatus::available;
}

//canSeat & availableSeat function
bool Table::canSeat(int guest) const {
    return guest > 0 && guest <= capacity && status == tableStatus::available;
}

std::string Table::stringStatus() const {
    switch (status) {
        case tableStatus::available : return "Available";
        case tableStatus::occupied: return "Occupied";
        case tableStatus::reserved: return "Reserved";
        }
    return "Unknown";
    }
