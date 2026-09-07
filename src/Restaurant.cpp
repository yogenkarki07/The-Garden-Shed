#include "../include/Restaurant.h"
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
    std::cout << std:: left << std::setw(8) << "Name" <<
        std::setw(10)<< "Capacity" <<
        std::setw(12) << "Status" <<
        "Reservation" << std::endl;
    std::cout << " ------------------------------------------------------- \n";

    for (auto table : tables) {
        std::cout << std::left << std::setw(8) << table.getTableNumber()
        << std::setw(10) << table.getCapacity() << std::setw(12) << table.stringStatus()
        << (table.getReservationName().empty()? "-" : table.getReservationName()) << std::endl;
    }
    std::cout << " ====================================================== \n";
}

//findOrder Function
Order* Restaurant::findOrder(int id) {
    for (auto& o : orders) {
        if (o.getOrderId() == id) {
            return &o;
        }
    }
    return nullptr;
}

//getOrders function
const std::vector<Order>& Restaurant::getOrders() const {
    return orders;
}

int Restaurant::nextOrderId() const {
    int nextId = 0;
    for (auto& o : orders) {
        if (o.getOrderId() > nextId) {
            nextId = o.getOrderId();
        }
    }
    return nextId + 1;
}

bool Restaurant::addOrder(const Order &order) {
    if (findOrder(order.getOrderId()) || !findTable(order.getTableNumber())) {
        return false;
    }
    orders.push_back(order);
    return true;
}

bool Restaurant::editOrder(int id, const Order &replacement) {
    Order* order = findOrder(id);
    if (!order) {
        std::cout << "Order not found !\n";
        return false;
    }
    *order = replacement;
    return true;
}

bool Restaurant::deleteOrder(int id) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getOrderId() == id) {
            orders.erase(it);
            std::cout << "Order deleted !\n";
            return true;
        }
    }
    std::cout << "Order not found !\n";
    return false;
}

//Table reservations
void Restaurant::markTableAsOccupied(int tableNumber) {
    if (auto* t = findTable(tableNumber)) {
        t->setStatus(TableStatus::occupied);
    }
}

void Restaurant::markTableAsAvailable(int tableNumber) {
    if (auto* t = findTable(tableNumber)) {
        bool stillActive = false;
        for (const auto& o : orders) {
            if (o.getTableNumber() == tableNumber &&
               o.getStatus() != orderStatus::served &&
               o.getStatus() != orderStatus::cancelled) {
                stillActive = true;
                break;
                }
        }
        if (!stillActive) {
            t->setStatus(TableStatus::available);
        }
    }
}

void Restaurant::displayAllOrders(const std::string& date) const{
    std::cout << " ======================  ORDER INFO  =================== \n" ;
    for (auto& o : orders) {
        if (date.empty() || o.getDate() == date) {
            o.displayOrderInfo();
        }
    }
}
