#include "Waiter.h"
#include "Restaurant.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Restaurant.h"

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
    out << std::put_time(&tm, "%Y-%m-%d %H:%M");
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
        std::cout << "Choose :";
        std:: cin >> readInt(choice);
    }

}



