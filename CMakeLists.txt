cmake_minimum_required(VERSION 4.2)
project(The_Garden_Shed)

set(CMAKE_CXX_STANDARD 20)

add_executable(The_Garden_Shed src/main.cpp
        src/Menu.cpp
        include/Menu.h
        src/MenuItem.cpp
        include/MenuItem.h
        src/CSVmanager.cpp
        include/CSVmanager.h
        src/Restaurant.cpp
        include/Restaurant.h
        src/Table.cpp
        include/Table.h
        src/OrderItem.cpp
        include/OrderItem.h
        src/Order.cpp
        include/Order.h
        src/Staff.cpp
        include/Staff.h
        src/Waiter.cpp
        include/Waiter.h
        src/Kitchen.cpp
        include/Kitchen.h
        src/Manager.cpp
        include/Manager.h)
