#pragma once
#include<string>

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

    //getters to reader the value
    int getTableNumber() const;
    int getCapacity() const;
    TableStatus getStatus() const;
    std::string getReservationName() const;
    std::string getReservationDateTime() const;

    //setters to modify the value
    void setCapacity(int value);
    void setStatus(TableStatus value);

    //functions
    void reserve(const std::string& name, const std::string& dataTime );
    void clearReservation();

    bool canSeat(int guest) const;
    std::string stringStatus() const;
};