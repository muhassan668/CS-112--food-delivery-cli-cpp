#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <iostream>
#include <string>
#include "Restaurent.h"
#include "Cart.h"
#include "Order.h"
#include "Payment.h"
#include "FileManager.h"

using namespace std;

class CommandHandler
{
private:
    Restaurant* restaurants;
    int restaurantCount;
    int restaurantCapacity;

    Order* orders;
    int orderCount;
    int orderCapacity;

    Cart cart;
    int currentCustomerId;
    int currentCartRestaurantId;
    int nextOrderId;
    int nextPaymentId;

    FileManager fileManager;

    void resizeOrders();
    int findRestaurantIndexById(int restaurantId) const;
    int findOrderIndexById(int orderId) const;
    MenuItem findMenuItemInRestaurant(int restaurantId, int itemId, bool& found) const;
    void initializeData();

public:
    CommandHandler();
    ~CommandHandler();

    void start();
    bool processCommand(string line);
};

#endif