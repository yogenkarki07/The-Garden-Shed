#include "../include/Restaurant.h"
#include "../include/Manager.h"
#include <iostream>
#include <string>
#include <ctime>

//static functions to avoid objects
static int mInt(std::string prompt) {
    int value;
    while(true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid Number !\n";
    }
}

static double mDouble(std::string prompt) {
    double value;
    while(true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid / Negative Amount!\n";
    }
}

static std::string mLine(std::string prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin >> std::ws, value);
    return value;
}

static std::string mDateLine(std::string prompt) {
    std::cout << prompt;
    std::cin.ignore(1000, '\n');
    std::string value;
    std::getline(std::cin, value);
    return value;
}

Manager::Manager(int id, std::string name) : Staff(id, name) {}

std::string Manager::role() const {
    return "Manager";
}

void Manager::displayDashboard(Restaurant& restaurant) {
    std::cout << " ================   MANAGER DASHBOARD   ============= \n";
    while (true) {
        std::cout << " 1. Menu Management \n" <<
                     " 2. Table Management \n" <<
                     " 3. Order Management \n" <<
                     " 4. Daily Sales Report \n" <<
                     " 5. Save Data \n" <<
                     " 6. Exit \n" ;
        int choice = mInt("Enter Choice: ");
        switch (choice) {
            case 1:
                menuManagement(restaurant);
                break;
            case 2:
                tableManagement(restaurant);
                break;
            case 3:
                orderManagement(restaurant);
                break;
            case 4:
                dailySalesReport(restaurant);
                break;
            case 5:
                std::cout << (restaurant.saveData() ? "Data saved! \n" : "Failed to save data! \n");
                break;
            case 6:
                return;
            default:
                std::cout << "Invalid Choice!\n";
                break;
        }
    }
}

//menu management -- function
void Manager::menuManagement(Restaurant &restaurant) {
    while (true) {
        std::cout << "  --- MENU MANAGEMENT ---  \n" ;
        std::cout << "  1. Add item \n"
                     "  2. View items \n"
                     "  3. Edit item \n"
                     "  4. Delete item \n"
                     "  5. Exit \n";
        int choice = mInt("Enter Choice: ");

        switch (choice) {
            case 1:
            {
                int id = restaurant.getMenu().nextId();
                std::string name = mLine("Name: ");
                std::string category = mLine("Category: ");
                std::string description = mLine("Description: ");
                double price = mDouble("Price: ");

                restaurant.getMenu().addItem(MenuItem(id, name, category, description, price, true));
                restaurant.saveData();
                std::cout << "Menu item with ID: " << id << " added !\n";
            }
                break;
            case 2:
                restaurant.getMenu().displayMenu();
                break;
            case 3:
            {
                int id = mInt("Enter Item ID to edit: ");
                MenuItem* oldItem = restaurant.getMenu().findItem(id);
                if (!oldItem) {
                    std::cout << "Item ID not found!\n";
                    continue;
                }

                std::string name = mLine("New name: ");
                std::string category = mLine(" New Category: ");
                std::string description = mLine(" New Description: ");
                double price = mDouble(" New Price: ");
                int available = mInt("Available? 1=Yes, 0=No: ");

                restaurant.getMenu().editItem(id, MenuItem(id, name, category, description, price, available == 1));
                restaurant.saveData();
                std::cout << "Menu item with ID: " << id << " updated!\n";
            }
                break;
            case 4:
            {
                int id = mInt(" Enter Item ID to edit: ");
                if (restaurant.getMenu().deleteItem(id)) {
                    restaurant.saveData();
                    std::cout << "Menu item with ID: " << id << " deleted.\n";
                }else{
                    std::cout << "Item ID not found!\n";
                }
            }
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid Choice!\n";
                break;
        }
    }
}

//Table management -- function
void Manager::tableManagement(Restaurant& restaurant) {
    while (true) {
        std::cout << " --- TABLE MANAGEMENT ---  \n" ;
        std::cout << "  1. Add table \n"
                     "  2. View table \n"
                     "  3. Edit table \n"
                     "  4. Delete table \n"
                     "  5. Reserve table \n"
                     "  6. Clear reservation \n"
                     "  7. Exit \n";
        int choice = mInt("Enter Choice: ");
        switch (choice) {
            case 1:
            {
                int number = mInt("Table Number: ");
                int capacity = mInt("Capacity: ");
                if (restaurant.addTable(Table(number, capacity))) {
                    restaurant.saveData();
                    std::cout << "New Table with number #" << number <<  " added\n";
                }else {
                    std::cout << "Table number already exists!\n";
                }
            }
                break;
            case 2:
                restaurant.displayTables();
                break;
            case 3:
            {
                int number = mInt("Table Number: ");
                Table* oldTable = restaurant.findTable(number);
                if (!oldTable) {
                    std::cout << "Table number not found!\n";
                    continue;
                }
                int capacity = mInt("New capacity: ");

                Table replacement(number, capacity, oldTable->getStatus());
                if (oldTable->getStatus() == tableStatus::reserved) {
                    replacement.reserveTable(oldTable->getReservationName(), oldTable->getReservationDateTime());
                }
                restaurant.editTable(number, replacement);
                restaurant.saveData();
                std::cout << "Table number #"<< number<< " updated ! \n";
            }
                break;
            case 4:
            {
                int number = mInt("Table number: ");
                if (restaurant.deleteTable(number)) {
                    restaurant.saveData();
                    std::cout << "Table number #" << number << " deleted! \n";
                }else {
                    std::cout << "Table does not exist!\n";
                }
            }
                break;
            case 5:
            {
                int number = mInt("Table number: ");
                Table* table = restaurant.findTable(number);
                if (!table) {
                    std::cout << "Table number not found!\n";
                    continue;
                }
                std::string name = mLine("Reservation name: ");
                std::string time = mLine(" Reservation date/time (YYYY-MM-DD  HH-MM): ");
                table->reserveTable(name, time);
                restaurant.saveData();
                std::cout << "Table number #" << number << " reserved!\n";
            }
                break;
            case 6:
            {
                int number = mInt("Table number: ");
                Table* table = restaurant.findTable(number);
                if (table) {
                    table->clearTableReservation();
                    restaurant.saveData();
                    std::cout << "Reservation cleared !!" << std::endl;
                }else {
                    std::cout << "Reservation not found!\n";
                }
            }
                break;
            case 7:
                return;
            default:
                std::cout << "Invalid Choice!\n";
                break;
        }
    }
}

//order management -- function
void Manager::orderManagement(Restaurant &restaurant) {
    while (true) {
        std::cout << " --- ORDER MANAGEMENT ---  \n" ;
        std::cout << "  1. View all orders \n"
                     "  2. View today's order \n"
                     "  3. Edit order \n"
                     "  4. Delete order \n"
                     "  5. Exit \n";
        int choice = mInt("Enter Choice: ");
        switch (choice) {
            case 1:
                restaurant.displayAllOrders();
                break;
            case 2:
            {
                restaurant.displayAllOrders([] {
                    auto now = std::time(nullptr);
                    std::tm tm{};
#ifdef _WIN32
                    localtime_s(&tm, &now);
#else
                    localtime_r(&now, &tm);
#endif
                    char buffer [11] {};
                    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
                    return std::string(buffer);
                }());
            }
                break;
            case 3: {
                int id = mInt("Order ID: ");
                Order* order = restaurant.findOrder(id);
                if (!order) {
                    std::cout << "Order ID not found!\n";
                    continue;
                }
                std::cout << " --- EDIT ORDER ---  \n"
                             "1. Change Table \n"
                             "2. Change Customer\n"
                             "3. Change Instruction\n"
                             "4. Change Status\n" ;
                int option = mInt("Choice: ");
                switch (option) {
                    case 1: {
                        int table = mInt("New Table number: ");
                        if (restaurant.findTable(table)) {
                            order->setTableNumber(table);
                        }else {
                            std::cout << "Table not found \n";
                        }
                    }
                        break;
                    case 2:
                        order->setCustomerName(mLine("New customer name: "));
                        break;
                    case 3:
                        order->setSpecialInstruction(mLine("New instruction: "));
                        break;
                    case 4: {
                        std::cout << " --- STATUS INFO ---\n";
                        std::cout << " 1. Pending \n"
                                     " 2. Preparing \n"
                                     " 3. Ready \n"
                                     " 4. Served \n"
                                     " 5. Cancelled \n";
                        int status = mInt("Choice: ");
                        if (status == 1) {
                            order->setStatus(orderStatus::pending);
                        }
                        else if (status == 2) {
                            order->setStatus(orderStatus::preparing);
                        }
                        else if (status == 3) {
                            order->setStatus(orderStatus::ready);
                        }
                        else if (status == 4) {
                            order->setStatus(orderStatus::served);
                        }else if (status == 5) {
                            order->setStatus(orderStatus::cancelled);
                        }else {
                            std::cout << "Invalid Choice!\n";
                        }
                    }
                        restaurant.saveData();
                        std::cout << "Order with ID #" << id << " updated\n";
                        break;
                        case 5:
                            return;
                        default:
                            std::cout << "Invalid Choice!\n";
                        break;
                    }
                }
                break;
            case 4:
            {
                int id = mInt("Enter Order ID: ");
                if (restaurant.deleteOrder(id)) {
                    restaurant.saveData();
                    std::cout << "Order with ID #" << id << " deleted\n";
                }else {
                    std::cout << "Order not found!\n";
                }
            }
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid Choice!\n";
                break;
        }
    }
}

//dailySalesReport
void Manager::dailySalesReport(Restaurant &restaurant) {
    std::string date = mDateLine("Report date (YYYY-MM-DD, blank = today): ");
    if (date.empty()) date = [] {
            auto now = std::time(nullptr);
            std::tm tm{};
#ifdef _WIN32
            localtime_s(&tm, &now);
#else
            localtime_r(&now, &tm);
#endif
            char buffer [11] {};
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
            return std::string(buffer);
        }();
    restaurant.generateSalesReport(date);
}