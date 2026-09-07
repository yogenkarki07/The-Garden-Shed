#include "../include/Table.h"
#include <iostream>

//Default constructor
Table::Table() : tableNumber(0), capacity(0), status(TableStatus::available){}

// Parameterized constructor
Table::Table(int number, int capacity, TableStatus status) : tableNumber(number), capacity(capacity), status(status){}

//getters
int Table::getTableNumber() const{
    return tableNumber;
}

int Table::getCapacity() const {
    return capacity;
}

TableStatus Table::getStatus() const {
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

void Table::setStatus(TableStatus value) {
    status = value;
}

//reserve function
void Table::reserve(const std::string& name, const std::string& dateTime) {
    reservationName = name;
    reservationDateTime = dateTime;
    status = TableStatus::reserved;
}

//clearReservation function
void Table::clearReservation() {
    reservationName.clear();
    reservationDateTime.clear();
    status = TableStatus::available;
}

//canSeat & availableSeat function
bool Table::canSeat(int guest) const {
    return guest > 0 && guest <= capacity && status == TableStatus::available;
}

std::string Table::stringStatus() const {
    switch (status) {
        case TableStatus::available : return "Available";
        case TableStatus::occupied: return "Occupied";
        case TableStatus::reserved: return "Reserved";
        }
    return "Unknown";
    }
