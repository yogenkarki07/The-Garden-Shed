#include "../include/CSVmanager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

namespace {
    // escapeCSV function to convert normal C++ string into a CSV-safe string
    std::string escapeCSV(const std::string& value) {
        bool quote = value.find_first_of(",\"\n") != std::string::npos;
        if (!quote) {
            return value;
        }
        std::string result = "\"";
        for (char c : value) {
            if (c == '"') {
                result += "\"\"";
            }else{
                result += c;}
        }
        result += '"';
        return result;
    }

    // parseCSVline function
    std::vector<std::string> parseCSVLine(std::string& line) {
        std::vector<std::string> fields;
        std::string field;
        bool quoted = false;

        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            if (c == '"') {
                if (quoted && i + 1 < line.size() && line[i + 1] == '"') {
                    field += '"';
                    ++i;
                }else {
                    quoted != quoted;
                }
            }else if (c == ',' && !quoted) {
                fields.push_back(field);
                field.clear();
            }else{
                field += c;
            }
        }
        fields.push_back(field);
        return fields;
    }
}

// private files path functions
std::string CSVmanager::menuFile() const{
     return dataDirectory + "/menu.csv";
}

std::string CSVmanager::tablesFile() const {
    return dataDirectory + "/table.csv";
}

std::string CSVmanager::orderItemsFile() const {
    return dataDirectory + "/OrderItem.csv";
}

std::string CSVmanager::ordersFile() const {
    return dataDirectory + "/Order.csv";
}

//constructor
CSVmanager::CSVmanager(const std::string& dataDirectory) : dataDirectory(dataDirectory) {}

//saveMenu function
bool CSVmanager::saveMenu(const Menu& menu) const {
    std::ofstream out(menuFile());
    if (!out) {
        std::cout << "Could not open file \n";
        return false;
    }

    out << "item_id, Name, dategory, description, price, available\n " ;

    for (const auto& item : menu.getItems()) {
        out << item.getId() << ',' << escapeCSV(item.getName()) << ','
        << escapeCSV(item.getCategory()) << ',' << escapeCSV(item.getDescription())
        << ',' << item.getPrice() << ',' << item.isAvailable() << '\n';
    }
    return true;
}

//loadMenu function
bool CSVmanager::loadMenu(Menu& menu) const {
    std::ifstream in(menuFile());
    if (!in) {
        std::cout << "Could not open file \n";
        return false;
    }
    menu.clear();
    std::string line;
    std::getline(in, line);

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto f = parseCSVLine(line);
        if (f.size() < 6) continue;

        try {
            menu.addItem(MenuItem(
                std::stoi(f[0]), f[1], f[2], f[3],
                std::stod(f[4]), f[5] == "1"));
        }catch (...) {
        }
    }
    return true;
}

//saveTable function
bool CSVmanager::saveTable(const std::vector<Table> &tables) const {
    std::ofstream out(tablesFile());
    if (!out) {
        std::cout << "Could not open file \n";
        return false;
    }

    out << "table_number, capacity, status, reservation_name, reservation_datetime \n" ;

    for (const auto& table : tables) {
        out << table.getTableNumber() << ',' << table.getCapacity() << ',' << table.stringStatus() << ','
        << escapeCSV(table.getReservationName()) << ',' << escapeCSV(table.getReservationDateTime()) << '\n';
    }
    return true;
}

//loadTable function
bool CSVmanager::loadTable(std::vector<Table>& tables) const {
    std::ifstream in(tablesFile());
    if (!in) {
        std::cout << "Could not open file \n";
        return false;
    }

    tables.clear();
    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto f = parseCSVLine(line);
        if ( f.size() < 5) continue;
        try {
            tableStatus status = tableStatus::available;
            if (f[2] == "occupied") {
                status = tableStatus::occupied;
            } else if (f[2] == "reserved") {
                status = tableStatus::reserved;
            }
            Table table(std::stoi(f[0]), std::stoi(f[1]), status);
            if (status == tableStatus::available) {
                table.reserve(f[3], f[4]);
            }
            tables.push_back(table);
        }catch (...) {

        }
    }
    return true;
}

//saveOrders function
bool CSVmanager::saveOrders( const std::vector<Order> &orders) const {
    std::ofstream ordersOut(ordersFile());
    std::ofstream itemsOut(orderItemsFile());
    if (!itemsOut || !ordersOut) {
        std::cout << "Could not open file \n";
        return false;
    }

    ordersOut << "order_id, table_number, customer_name, special_instruction, status, order_dateTime, total" << std::endl;
    itemsOut << "order_id, item_id, item_name, item_price, item_quantity" << std::endl;

    for (const auto& order : orders) {
        ordersOut << order.getOrderId() << ","
                  << order.getTableNumber() << ","
                  << escapeCSV(order.getCustomerName()) << ","
                  << escapeCSV(order.getSpecialInstruction()) << ","
                  << order.statusString() << ","
                  << order.getOrderDateTime() << ","
                  << std::fixed << std::setprecision(2) << order.getTotalOrderPrice() << ","
                  << std::endl;

        for (const auto& item : order.getItems()) {
            itemsOut << order.getOrderId() << ","
                     << item.getMenuItemId() << ","
                     << escapeCSV(item.getItemName()) << ","
                     <<std::fixed << std::setprecision(2) << item.getItemPrice() << ","
                     << item.getItemQuantity() << ","
                     << std::endl;
        }
    }
        return true;
}

//loadOrders function
bool CSVmanager::loadOrders(std::vector<Order>& orders, const Menu& menu) const {
    std::ifstream ordersIn(ordersFile());
    std::ifstream itemsIn(orderItemsFile());

    if (!ordersIn || !itemsIn) {
        std::cout << "Could not open file \n";
        return false;
    }

    orders.clear();

    std::string line;
    std::getline(ordersIn, line);
    while (std::getline(ordersIn, line)) {
        if (line.empty()) {
            continue;
        }
        auto f = parseCSVLine(line);
        if (f.size() < 7) {
            continue;
        }

        try {
            Order order ( std::stoi(f[0]), std::stoi(f[1]), f[2], f[4], f[5] );
            order.setStatus(Order::stringToStatus(f[3]));
        } catch (...){}
    }

    std::getline(itemsIn, line);
    while (std::getline(itemsIn, line)) {
        if (line.empty()) {
            continue;
        }
        auto f = parseCSVLine(line);
        if (f.size() < 5) {
            continue;
        }

        try {
            int orderId = std::stoi(f[0]);
            for (auto &order : orders) {
                if (order.getOrderId() == orderId) {
                    order.addItem(OrderItem(
                        std::stoi(f[1]), f[2], std::stoi(f[3]), std::stoi(f[4])
                        ));
                    orders.push_back(order);
                }
            }
        }catch (...){}
    }
    return true;
}