#ifndef RESTAURENT_H
#define RESTAURENT_H

#include <iostream>
#include <string>
#include "MenuItem.h"
using namespace std;

// Represents one restaurant and its menu
class Restaurant
{
private:
    int restaurantId;
    string restaurantName;
    string location;

    MenuItem* menuItems;
    int itemCount;
    int capacity;

    // Resizes menu array when full
    void resizeMenu();

public:
    Restaurant();
    Restaurant(int restaurantId, string restaurantName, string location);
    Restaurant(const Restaurant& other);
    Restaurant& operator=(const Restaurant& other);
    ~Restaurant();

    int getRestaurantId() const;
    string getRestaurantName() const;
    string getLocation() const;
    int getItemCount() const;

    void setRestaurantName(string restaurantName);
    void setLocation(string location);

    void addMenuItem(const MenuItem& item);
    void removeMenuItem(int itemId);
    int findMenuItemIndexById(int itemId) const;
    MenuItem getMenuItemAt(int index) const;

    void displayRestaurant() const;
    void displayMenu() const;
};

#endif