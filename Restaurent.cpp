#include "Restaurent.h"

// Default constructor
Restaurant::Restaurant()
{
    restaurantId = 0;
    restaurantName = "";
    location = "";
    capacity = 5;
    itemCount = 0;
    menuItems = new MenuItem[capacity];
}

// Parameterized constructor
Restaurant::Restaurant(int restaurantId, string restaurantName, string location)
{
    this->restaurantId = restaurantId;
    this->restaurantName = restaurantName;
    this->location = location;
    capacity = 5;
    itemCount = 0;
    menuItems = new MenuItem[capacity];
}

// Copy constructor for deep copy
Restaurant::Restaurant(const Restaurant& other)
{
    restaurantId = other.restaurantId;
    restaurantName = other.restaurantName;
    location = other.location;
    capacity = other.capacity;
    itemCount = other.itemCount;

    menuItems = new MenuItem[capacity];
    for (int i = 0; i < itemCount; i++)
    {
        menuItems[i] = other.menuItems[i];
    }
}

// Assignment operator for deep copy
Restaurant& Restaurant::operator=(const Restaurant& other)
{
    if (this != &other)
    {
        delete[] menuItems;

        restaurantId = other.restaurantId;
        restaurantName = other.restaurantName;
        location = other.location;
        capacity = other.capacity;
        itemCount = other.itemCount;

        menuItems = new MenuItem[capacity];
        for (int i = 0; i < itemCount; i++)
        {
            menuItems[i] = other.menuItems[i];
        }
    }
    return *this;
}

// Destructor to free dynamic memory
Restaurant::~Restaurant()
{
    delete[] menuItems;
}

// Doubles the menu array size
void Restaurant::resizeMenu()
{
    capacity = capacity * 2;
    MenuItem* newMenu = new MenuItem[capacity];

    for (int i = 0; i < itemCount; i++)
    {
        newMenu[i] = menuItems[i];
    }

    delete[] menuItems;
    menuItems = newMenu;
}

int Restaurant::getRestaurantId() const
{
    return restaurantId;
}

string Restaurant::getRestaurantName() const
{
    return restaurantName;
}

string Restaurant::getLocation() const
{
    return location;
}

int Restaurant::getItemCount() const
{
    return itemCount;
}

void Restaurant::setRestaurantName(string restaurantName)
{
    this->restaurantName = restaurantName;
}

void Restaurant::setLocation(string location)
{
    this->location = location;
}

// Adds a new item to the restaurant menu
void Restaurant::addMenuItem(const MenuItem& item)
{
    if (itemCount == capacity)
    {
        resizeMenu();
    }

    menuItems[itemCount] = item;
    itemCount++;
}

// Searches for a menu item by id
int Restaurant::findMenuItemIndexById(int itemId) const
{
    for (int i = 0; i < itemCount; i++)
    {
        if (menuItems[i].getItemId() == itemId)
        {
            return i;
        }
    }
    return -1;
}

MenuItem Restaurant::getMenuItemAt(int index) const
{
    if (index >= 0 && index < itemCount)
    {
        return menuItems[index];
    }

    return MenuItem();
}

// Removes a menu item from the array
void Restaurant::removeMenuItem(int itemId)
{
    int index = findMenuItemIndexById(itemId);

    if (index == -1)
    {
        cout << "Menu item not found." << endl;
        return;
    }

    for (int i = index; i < itemCount - 1; i++)
    {
        menuItems[i] = menuItems[i + 1];
    }

    itemCount--;
}

// Displays restaurant basic information
void Restaurant::displayRestaurant() const
{
    cout << "Restaurant ID: " << restaurantId << endl;
    cout << "Restaurant Name: " << restaurantName << endl;
    cout << "Location: " << location << endl;
}

// Displays all items in the menu
void Restaurant::displayMenu() const
{
    cout << "----- Menu of " << restaurantName << " -----" << endl;

    if (itemCount == 0)
    {
        cout << "No menu items available." << endl;
        return;
    }

    for (int i = 0; i < itemCount; i++)
    {
        menuItems[i].displayItem();
        cout << "------------------------" << endl;
    }
}