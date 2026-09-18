# The Garden Shed — Restaurant Management System

A console-based Restaurant Management System, built with an
object-oriented design. The system supports three staff roles — **Manager**,
**Waiter**, and **Kitchen** — each with a dedicated dashboard, and persists
all data (menu, tables, orders) to CSV files so information survives between
runs.

## Features

- **Menu management** — add, edit, delete, and browse menu items (name,
  category, description, price, availability).
- **Table management** — add, edit, delete tables, and track table status
  (`available`, `occupied`, `reserved`), including reservations.
- **Order management** — create orders against a table, add/remove/update
  order items, track order status (`pending` → `preparing` → `ready` →
  `served`, or `cancelled`), and calculate order totals.
- **Kitchen queue** — a live view of orders still in progress, for kitchen
  staff.
- **Sales reporting** — daily income, order counts, and the best-selling
  item for a given date.
- **CSV persistence** — the menu, tables, and orders are loaded from and
  saved to CSV files in the `data/` directory via a dedicated `CSVmanager`,
  so the restaurant's state is not lost on exit.
- **Role-based dashboards** — a `Staff` base class defines a common
  interface, with `Manager`, `Waiter`, and `Kitchen` each implementing their
  own dashboard and permissions.

## Project structure

```
The-Garden-Shed/
├── include/            Header files (class declarations)
│   ├── CSVmanager.h
│   ├── Kitchen.h
│   ├── Manager.h
│   ├── Menu.h
│   ├── MenuItem.h
│   ├── Order.h
│   ├── OrderItem.h
│   ├── Restaurant.h
│   ├── Staff.h
│   ├── Table.h
│   └── Waiter.h
├── src/                Source files (class implementations + entry point)
│   ├── CSVmanager.cpp
│   ├── Kitchen.cpp
│   ├── main.cpp
│   ├── Manager.cpp
│   ├── Menu.cpp
│   ├── MenuItem.cpp
│   ├── Order.cpp
│   ├── OrderItem.cpp
│   ├── Restaurant.cpp
│   ├── Staff.cpp
│   ├── Table.cpp
│   └── Waiter.cpp
├── data/               CSV data files (menu, tables, orders) — created/used at runtime
├── CMakeLists.txt      CMake build configuration
└── README.md
```

## Design overview

| Class | Responsibility |
|---|---|
| `MenuItem` | A single dish: id, name, category, description, price, availability. |
| `Menu` | Owns a collection of `MenuItem`s; add/edit/delete/find/list. |
| `Table` | A physical table: number, capacity, `tableStatus`, and reservation details. |
| `OrderItem` | A line item within an order: menu item id, name, price, quantity. |
| `Order` | A customer order for a table; owns a collection of `OrderItem`s and an `orderStatus`. |
| `CSVmanager` | Reads and writes `Menu`, `Table`, and `Order` data to/from CSV files. |
| `Restaurant` | The central hub: owns the `Menu`, all `Table`s, all `Order`s, and the `CSVmanager`; exposes management and reporting operations. |
| `Staff` | Abstract base class for restaurant staff (`staffId`, `name`) defining the `role()` and `displayDashboard()` interface. |
| `Manager` / `Waiter` / `Kitchen` | Concrete staff roles, each overriding `role()` and `displayDashboard()` with role-specific behavior. |

Key object-oriented concepts demonstrated:

- **Encapsulation** — all class data members are private (or protected in
  `Staff`), accessed only through public getters/setters.
- **Abstraction** — `Staff` is an abstract class exposing a simple interface
  (`role()`, `displayDashboard()`) while hiding each role's internal logic.
- **Inheritance** — `Manager`, `Waiter`, and `Kitchen` all inherit from
  `Staff`.
- **Polymorphism** — `displayDashboard()` and `role()` are declared
  `virtual` in `Staff` and overridden per role; `Menu::findItem` also
  demonstrates compile-time polymorphism via overloading (const/non-const).
- **Composition** — `Restaurant` owns its `Menu`, `Table`s, `Order`s, and
  `CSVmanager`; `Menu` owns its `MenuItem`s; `Order` owns its `OrderItem`s.
  These parts do not outlive their whole.

See `docs/UML-Class-Diagram` (or the diagram supplied alongside this
project) for the full class diagram, including attribute/method visibility
and all relationships.

## Requirements

- A C++ compiler with **C++20** support (e.g. GCC 10+, Clang 11+, MSVC 2019+).
- **CMake** 3.x or newer (the project's `CMakeLists.txt` specifies a minimum
  of 4.2 — lower it if your local CMake version is older).

## Building

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

This produces an executable named `The_Garden_Shed` (or
`The_Garden_Shed.exe` on Windows).

## Running

Run the executable from the project root (so it can find/create the
`data/` directory):

```bash
./build/The_Garden_Shed
```

On first run, if `data/` is empty, the program seeds a default set of 10
tables and a starter menu, then saves them to CSV.

### Using the app

You'll be prompted to choose a role:

```
========== The Garden Shed =========
 1. Waiter
 2. Kitchen
 3. Manager
 4. Exit
====================================
```

- **Waiter** — take/manage orders for tables.
- **Kitchen** — view the current kitchen queue of in-progress orders.
- **Manager** — manage the menu, tables, and orders, and generate daily
  sales reports.

Data is saved back to the CSV files in `data/` as changes are made, so
progress persists between sessions.

## Data files

| File | Contents |
|---|---|
| `data/menu.csv` | All menu items. |
| `data/table.csv` | All tables and their current status/reservations. |
| `data/Order.csv` | All orders (header/summary information). |
| `data/OrderItem.csv` | The line items belonging to each order. |

## Notes

- The CMake minimum version in `CMakeLists.txt` is set high (4.2); adjust
  it to match your installed CMake if the build fails on that line.
- `Order::statusTostring` / `Order::stringToStatus` and the equivalent
  string helpers on `Table` handle conversion between the `enum class`
  status types and their CSV/display text representations.
