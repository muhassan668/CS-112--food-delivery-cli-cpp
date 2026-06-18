#include "MenuItem.h"

// Default constructor
MenuItem::MenuItem()
{
    itemId = 0;
    itemName = "";
    price = 0.0;
    category = "";
    isAvailable = true;
}

// Parameterized constructor
MenuItem::MenuItem(int itemId, string itemName, double price, string category, bool isAvailable)
{
    this->itemId = itemId;
    this->itemName = itemName;
    this->price = price;
    this->category = category;
    this->isAvailable = isAvailable;
}

int MenuItem::getItemId() const
{
    return itemId;
}

string MenuItem::getItemName() const
{
    return itemName;
}

double MenuItem::getPrice() const
{
    return price;
}

string MenuItem::getCategory() const
{
    return category;
}

bool MenuItem::getIsAvailable() const
{
    return isAvailable;
}

void MenuItem::setItemName(string itemName)
{
    this->itemName = itemName;
}

void MenuItem::setPrice(double price)
{
    this->price = price;
}

void MenuItem::setCategory(string category)
{
    this->category = category;
}

void MenuItem::setIsAvailable(bool isAvailable)
{
    this->isAvailable = isAvailable;
}

// Displays menu item details
void MenuItem::displayItem() const
{
    cout << "Item ID: " << itemId << endl;
    cout << "Name: " << itemName << endl;
    cout << "Price: " << price << endl;
    cout << "Category: " << category << endl;
    cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
}