#pragma once
#include<string>

class MenuItem {
    int itemId;
    std::string name;
    std::string category;
    std::string description;
    double price;
    bool available;

    public:
    MenuItem();
    MenuItem(int itemId, std::string name, std::string category, std::string description, double price, bool available = true);

    //getters  (to read the private data)
    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getDescription() const;
    double getPrice() const;
    bool isAvailable() const;

    //setters   (to modify private data)
    // void setId(int value); --- Id should be stable. it should not be modified.
    void setName(const std::string &value);
    void setCategory(const std::string &value);
    void setDescription(const std::string &value);
    void setPrice(double value);
    void setAvailable(bool value);

};
