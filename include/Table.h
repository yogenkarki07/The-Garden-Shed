#pragma once
#include<string>

enum class tableStatus {
    available,
    occupied,
    reserved,
};

class Table {
    int tableNumber;
    int capacity;
    tableStatus status;
    std::string reservationName;
    std::string reservationDateTime;

    public:
    Table();
    Table(int number, int capacity, tableStatus status = tableStatus::available);

    //getters to reader the value
    int getTableNumber() const;
    int getCapacity() const;
    tableStatus getStatus() const;
    std::string getReservationName() const;
    std::string getReservationDateTime() const;

    //setters to modify the value
    void setCapacity(int value);
    void setStatus(tableStatus value);

    //functions
    void reserveTable(const std::string& name, const std::string& dataTime );
    void clearTableReservation();

    bool availableTable(int guest);
    bool occupyTable();
    bool freeTable();

    std::string stringStatus() const;
};