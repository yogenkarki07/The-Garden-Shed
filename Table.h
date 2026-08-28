#pragma once
#include<string>
#include<vector>

enum TableStatus {
    available,
    occupied,
    reserved,
};

class Table {
    int tableNumber;
    int capacity;
    TableStatus status;
    std::string reservationName;
    std::string reservationDateTime;

    public:
    Table();
    Table(int number, int capacity, TableStatus status = TableStatus::available);

    void setTableNumber(int number);
    void setCapacity(int capacity);
};