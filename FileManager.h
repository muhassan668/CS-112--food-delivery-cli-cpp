#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "User.h"
#include "DeliveryAgent.h"
#include "Restaurent.h"
#include "Order.h"

using namespace std;

class FileManager
{
private:
    UserRole stringToUserRole(const string& roleText);
    OrderStatus stringToOrderStatus(const string& statusText);
    PaymentType stringToPaymentType(const string& paymentTypeText);
    PaymentStatus stringToPaymentStatus(const string& paymentStatusText);

public:
    void saveUser(const User& user);
    void saveDeliveryAgent(const DeliveryAgent& agent);
    void saveRestaurant(const Restaurant& restaurant);
    void saveOrder(const Order& order);

    int loadRestaurants(Restaurant*& restaurants, int& capacity);
    void loadMenuItems(Restaurant* restaurants, int restaurantCount);
    int loadOrders(Order*& orders, int& capacity);
    void showDeliveryAgents();
    bool isDeliveryAgentAvailable(int agentId);
    void updateDeliveryAgentAvailability(int agentId, bool isAvailable);
};

#endif