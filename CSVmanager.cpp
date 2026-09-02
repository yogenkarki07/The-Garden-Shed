#include "CSVmanager.h"
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
            TableStatus status = TableStatus::available;
            if (f[2] == "occupied") {
                status = TableStatus::occupied;
            } else if (f[2] == "reserved") {
                status = TableStatus::reserved;
            }
            Table table(std::stoi(f[0]), std::stoi(f[1]), status);
            if (status == TableStatus::available) {
                table.reserve(f[3], f[4]);
            }
            tables.push_back(table);
        }catch (...) {

        }
    }
}

//saveOrders function
bool CSVmanager::saveOrders( const std::vector<Order> &orders) const {
    
}
