#ifndef MENUITEM_H
#define MENUITEM_H

#include <iostream>
#include <string>
using namespace std;

// Represents one food item in a restaurant menu
class MenuItem
{
private:
    int itemId;
    string itemName;
    double price;
    string category;
    bool isAvailable;

public:
    MenuItem();
    MenuItem(int itemId, string itemName, double price, string category, bool isAvailable = true);

    int getItemId() const;
    string getItemName() const;
    double getPrice() const;
    string getCategory() const;
    bool getIsAvailable() const;

    void setItemName(string itemName);
    void setPrice(double price);
    void setCategory(string category);
    void setIsAvailable(bool isAvailable);

    void displayItem() const;
};

#endif