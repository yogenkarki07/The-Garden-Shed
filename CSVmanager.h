#pragma once
#include "Menu.h"
#include "Table.h"
#include "OrderItem.h"
#include "Order.h"
#include <string>

#include "OrderItem.h"

class CSVmanager {
    std::string dataDirectory;
    std::string menuFile() const;
    std::string tablesFile() const;
    std::string orderItemsFile() const;
    std::string ordersFile() const;

public:
    explicit CSVmanager(const std::string &dataDirectory = "data");

    //Menu
    bool saveMenu(const Menu& menu) const;
    bool loadMenu(Menu& menu) const;

    //Table
    bool saveTable(const std::vector<Table>& tables) const;
    bool loadTable(std::vector<Table>& tables) const;

    // OrderItem - Order
     bool saveOrders(const std::vector<Order>& orders) const;
     bool loadOrders(std::vector<Order>& orders, const Menu& menu) const ;
};
