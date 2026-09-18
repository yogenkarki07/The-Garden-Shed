#include "../include/Restaurant.h"
#include<iostream>
#include<string>
#include <iomanip>
#include <map>

Restaurant::Restaurant(const std::string& directory) : csvManager(directory){}

//saveData function
bool Restaurant::saveData() const {
    bool menuSaved = csvManager.saveMenu(menu);
    bool tableSaved = csvManager.saveTable(tables);
    bool ordersSaved = csvManager.saveOrders(orders);
    return menuSaved && tableSaved && ordersSaved;
}

//loadData function
bool Restaurant::loadData() {
    bool menuLoaded = csvManager.loadMenu(menu);
    bool tableLoaded = csvManager.loadTable(tables);
    bool ordersLoaded = csvManager.loadOrders(orders, menu);
    return menuLoaded && tableLoaded && ordersLoaded;
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
bool Restaurant::addTable(const Table &table){
    if (findTable(table.getTableNumber())) {
        std::cout << "Table already exists !\n";
        return false;
    }
    tables.push_back(table);
    // std::cout << "Table added successfully !\n";
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
    // std::cout << "Table updated successfully !\n";
    return true;
}

//deleteTable function
bool Restaurant::deleteTable(int number) {
    for (auto table = tables.begin(); table != tables.end(); ++table) {
        if (table->getTableNumber() == number) {
            tables.erase(table);
            // std::cout << "Table removed successfully ! !\n";
            return true;
        }
    }
    std::cout << "Table not found !\n";
    return false;
}

//displayTables function
void Restaurant::displayTables() const {
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
        t->occupyTable();
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
            t->freeTable();
        }
    }
}

void Restaurant::displayAllOrders(const std::string& date) const{
    std::cout << " ======================  ORDER INFO  =================== \n" ;
    for (auto& o : orders) {
        if (date.empty() || o.getDate() == date) {
            o.displayOrderInfo();
            std::cout << " ------------------------------------------------------- \n" ;
        }
    }
}

//displaykitchenQueue function
void Restaurant::displayKitchenQueue() const{
    std::cout << " ====================== Kitchen Queue =================== \n" ;
    for (const auto& o : orders) {
        if (o.getStatus() != orderStatus::served && o.getStatus() != orderStatus::cancelled) {
            o.displayOrderInfo();
        }
    }
}

//sales --report/info
double Restaurant::totalIncome(const std::string& date) const {
    double total = 0;
    for (auto& o : orders) {
        if (o.getDate() == date && o.getStatus() == orderStatus::served) {
            total += o.getTotalOrderPrice();
        }
    }
    return total;
}

int Restaurant::orderCount(const std::string& date) const {
    int count = 0;
    for (auto& o : orders) {
        if (o.getDate() == date && o.getStatus() == orderStatus::served) {
            count++;
        }
    }
    return count;
}

std::pair<std::string, int> Restaurant::mostOrderedItem(const std::string& date) const {
    std::map<std::string, int> counts;
    for (auto& o : orders) {
        if (o.getDate() != date || o.getStatus() != orderStatus::served) continue;
        for (const auto& item : o.getItems()) {
            counts[item.getItemName()] += item.getItemQuantity();
        }
    }
        std::pair<std::string, int> result{"none", 0};
        for (const auto& [name, count] : counts) {
            if (count > result.second) result = { name, count };
        }
        return result;
}

void Restaurant::generateSalesReport(const std::string& date) const {
    int occupied = 0, reserved = 0, available = 0;

    for (const auto& t : tables) {
        if (t.getStatus() == tableStatus::occupied) ++occupied;
        else if (t.getStatus() == tableStatus::reserved) ++reserved;
        else ++available;
    }

    auto top = mostOrderedItem(date);

    std::map<std::string, int> itemCounts;
    int orderedItemUnits = 0;

    for (const auto& o : orders) {
        std::string orderDate = o.getOrderDateTime().substr(0, 10);
        if (orderDate != date || o.getStatus() != orderStatus::served) continue;

        for (const auto& item : o.getItems()) {
            itemCounts[item.getItemName()] += item.getItemQuantity();
            orderedItemUnits += item.getItemQuantity();
        }

    }

    std::cout << "\n ==================================================== \n";
    std::cout << "        THE GARDEN SHED - DAILY SALES-REPORT \n";
    std::cout << " ====================================================== \n";
    std::cout << "Date: " << date << "\n";
    std::cout << "TABLE OCCUPANCY\n";
    std::cout << "   Available : " << available << "\n";
    std::cout << "   Occupied  : " << occupied << "\n";
    std::cout << "   Reserved  : " << reserved << "\n";
    std::cout << "ORDERED OPERATIONS\n";
    std::cout << "   Number of orders   : " << orderCount(date) << '\n';
    std::cout << "   Ordered item units : " << orderedItemUnits << "\n";
    std::cout << "   Total Income       : " << totalIncome(date) << "\n";
    std::cout << "   Most ordered item  : " << top.first << " (" << top.second << " units)\n";
    std::cout << "ITEM BREAKDOWN \n";
    for (const auto& [name, count] : itemCounts) {
        std::cout << "   " << std::left << std::setw(30) << name << count << "\n";
    }
    std::cout << " ===================================================== \n";
}
