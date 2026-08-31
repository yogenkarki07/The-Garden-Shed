cmake_minimum_required(VERSION 4.2)
project(The_Garden_Shed)

set(CMAKE_CXX_STANDARD 20)

add_executable(The_Garden_Shed main.cpp
        Menu.cpp
        Menu.h
        MenuItem.cpp
        MenuItem.h
        CSVmanager.cpp
        CSVmanager.h
        Restaurant.cpp
        Restaurant.h
        Table.cpp
        Table.h
        OrderItem.cpp
        OrderItem.h
        Order.cpp
        Order.h)
