#include "../include/Waiter.h"
#include "../include/Restaurant.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

//static functions -- no need to create object
//readInt function -- helps to determine integer - number
static int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input ! \n";
    }
}

//todayDateTime function -- for date and time
static std::string todayDateTime() {
    auto now = std::time(nullptr);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &now);
#else
    localtime_r(&now, &tm);
#endif
    std::ostringstream out;
    out << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

//readLine function -- to check space along with a line of text
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::cin.ignore(1000, '\n');
    std::string value;
    std::getline(std::cin, value);
    return value;
}

//constructor -- to target Staff (parent)
Waiter::Waiter(int id, std::string name) : Staff(id, name) {}

std::string Waiter::role() const {
    return "Waiter";
}

void Waiter::displayDashboard(Restaurant& restaurant) {
    while (true) {
        std::cout << " ================   WAITER DASHBOARD   ============= \n";
        std::cout << " 1. View Tables \n" <<
                     " 2. View Menu \n" <<
                     " 3. Add new order \n" <<
                     " 4. View today's order \n" <<
                     " 5. Exit \n" ;
        int choice = readInt("Choose: ");
        switch (choice) {
            case 1:
                restaurant.displayTables();
                break;
            case 2:
                restaurant.getMenu().displayMenu();
                break;
            case 3:
            {
                //Order--part
                restaurant.displayTables();
                int tableNo = readInt("Table Number: ");
                Table* table = restaurant.findTable(tableNo);
                if (!table) {
                    std::cout << "Table does not exist ! \n";
                    continue;
                }
                if (table->getStatus() != tableStatus::available) {
                    std::cout << "Table is not available ! \n";
                    continue;
                }

                std::string customer = readLine("Customer Name: ");
                std::string instructions = readLine(" Special Instructions (optional): ");

                Order order(restaurant.nextOrderId(), tableNo, customer, instructions, todayDateTime());

                //order-items--part
                while (true) {
                    restaurant.getMenu().displayMenu();
                    int itemId = readInt("Menu Item Id (0 to finish): ");
                    if (itemId == 0) {
                        break;
                    }

                    const MenuItem* item = restaurant.getMenu().findItem(itemId);
                    if (!item) {
                        std::cout << "Invalid item \n";
                        continue;
                    }

                    if (!item->isAvailable()) {
                        std::cout << "Unavailable item \n";
                        continue;
                    }

                    int quantity = readInt("Quantity: ");
                    if (quantity <= 0) {
                        std::cout << "Quantity must be positive\n";
                        continue;
                    }

                    order.addItem(OrderItem(item->getId(), item->getName(), item->getPrice(), quantity));

                    std::cout << "Item added !\n";

                    if (order.getItems().empty()) {
                        std::cout << "Order cancelled. No item selected !\n";
                    }else {
                        restaurant.addOrder(order);
                        restaurant.saveData();
                        std::cout << "Order No: " << order.getOrderId() << " sent to kitchen.\n"
                        << " Total: $" << order.getTotalOrderPrice() << std::endl;
                    }
                }
            }
            break;

            case 4:
                restaurant.displayAllOrders(todayDateTime().substr(0,10));
                break;

            case 5:
                // std::cout << "back to main menu" << std::endl;
                return;

            default:
                std::cout << "Invalid choice \n";
                break;
        }
    }
}