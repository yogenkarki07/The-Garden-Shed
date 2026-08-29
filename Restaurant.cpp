#include "Restaurant.h"
#include<iostream>
#include<string>
#include <iomanip>

Restaurant::Restaurant(const std::string& directory) : csvManager(directory){}

//saveData function
bool Restaurant::saveData() const {
    bool menuSaved = csvManager.saveMenu(menu);
    bool tableSaved = csvManager.saveTable(tables);
    return menuSaved && tableSaved;
}

//loadData function
bool Restaurant::loadData() {
    bool menuLoaded = csvManager.loadMenu(menu);
    bool tableLoaded = csvManager.loadTable(tables);
    return menuLoaded && tableLoaded;
}

//Menu operations functions
Menu& Restaurant::getMenu() {
    return menu;
}

const Menu& Restaurant::getMenu() const {
    return menu;
}

//Table operations
//findTable function
Table* Restaurant::findTable(int number) {
    for (auto& t : tables) {
        if (t.getTableNumber() == number) {
            return& t;
        }
    }
    return nullptr;
}

//getTables function
const std::vector<Table>& Restaurant::getTables() const {
    return tables;
}

//addTable function
bool Restaurant::addTable(Table &table) {
    if (findTable(table.getTableNumber())) {
        std::cout << "Table already exists !\n";
        return false;
    }
    tables.push_back(table);
    std::cout << "Table added successfully !\n";
    return true;
}

//editTable function -- replacement is a parameter for updated table
bool Restaurant::editTable(int number, const Table &replacement) {
    Table* table = findTable(number);
    if (!table) {
        std::cout << "Table not found !\n";
        return false;
    }
    *table = replacement;  //replacement is used temporarily to store updated table details
    std::cout << "Table edited successfully !\n";
    return true;
}

//deleteTable function
bool Restaurant::deleteTable(int number) {
    for (auto table = tables.begin(); table != tables.end(); ++table) {
        if (table->getTableNumber() == number) {
            tables.erase(table);
            std::cout << "Table removed successfully ! !\n";
            return true;
        }
    }
    std::cout << "Table not found !\n";
    return false;
}

//displayTables function
void Restaurant::displayTables() {
    std::cout << " ====================  TABLE INFO  ==================== \n" ;
    std::cout << std:: left << std::setw(8) << "Name" << std::setw(10)
    << "Capacity" << std::setw(12) << "Status" << "Reservation" << std::endl;
    std::cout << " ------------------------------------------------------- \n";

    for (auto table : tables) {
        std::cout << std::left << std::setw(8) << table.getTableNumber()
        << std::setw(10) << table.getCapacity() << std::setw(12) << table.stringStatus()
        << (table.getReservationName().empty()? "-" : table.getReservationName()) << std::endl;
    }
    std::cout << " ====================================================== \n";
}
