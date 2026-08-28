#include "Table.h"
#include <iostream>

//Default constructor
Table::Table() : tableNumber(0), capacity(0), status(TableStatus::available){}

// Parameterized constructor
Table::Table(int number, int capacity, TableStatus status) : tableNumber(number), capacity(capacity), status(status){}

void Table::setTableNumber(int number) {
    return 
}