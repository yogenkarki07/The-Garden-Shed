#include "../include/Kitchen.h"
#include "../include/Restaurant.h"
#include<iostream>
#include<string>


//kitchenInt function -- helps to determine integer - number
static int kitchenInt(const std::string& prompt) {
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

//constructor -- to target Staff (parent)
Kitchen::Kitchen(int id, std::string name) : Staff(id, name) {}

std::string Kitchen::role() const {
    return "Kitchen Staff";
}

void Kitchen::displayDashboard(Restaurant &restaurant) {
    while (true) {
        std::cout << " ================   WAITER DASHBOARD   ============= \n";
        std::cout << " 1. View incoming orders \n" <<
                     " 2. Mark order Preparing \n" <<
                     " 3. Mark order Ready \n" <<
                     " 4. Mark order Served \n" <<
                     " 5. Exit \n" ;
        int choice = kitchenInt("Choose: ");

        if ( choice ==1) {
            restaurant.displayKitchenQueue();
        }

        else if ( choice >= 2 && choice <= 4) {
            restaurant.displayKitchenQueue();
            int id = kitchenInt("Order ID: ");
            Order* order = restaurant.findOrder(id);

            if (!order) {
                std::cout << "Order not found !\n";
                continue;
            }

            if (choice == 2) {
                order->setStatus(orderStatus::preparing);
            }
            else if (choice == 3) {
                order->setStatus(orderStatus::ready);
            }
            else {   //choice == 4
                order->setStatus(orderStatus::served);
                restaurant.markTableAsAvailable(order->getTableNumber());
            }

            restaurant.saveData();

            std::cout << "Order status updated to " << order->statusString() << std::endl;
        }

        else if (choice == 5) {
            return;
        }

        else {
            std::cout << "Invalid choice ! \n";
        }
    }
}
