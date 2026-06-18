#include "CommandHandler.h"
#include <sstream>

CommandHandler::CommandHandler()
{
    restaurants = nullptr;
    restaurantCount = 0;
    restaurantCapacity = 0;

    orders = nullptr;
    orderCount = 0;
    orderCapacity = 0;

    currentCustomerId = 1;
    currentCartRestaurantId = -1;
    nextOrderId = 1001;
    nextPaymentId = 5001;

    initializeData();
}

CommandHandler::~CommandHandler()
{
    delete[] restaurants;
    delete[] orders;
}

void CommandHandler::initializeData()
{
    restaurantCount = fileManager.loadRestaurants(restaurants, restaurantCapacity);
    fileManager.loadMenuItems(restaurants, restaurantCount);

    orderCount = fileManager.loadOrders(orders, orderCapacity);

    int maxOrderId = 1000;
    for (int i = 0; i < orderCount; i++)
    {
        if (orders[i].getOrderId() > maxOrderId)
        {
            maxOrderId = orders[i].getOrderId();
        }
    }
    nextOrderId = maxOrderId + 1;
}

void CommandHandler::resizeOrders()
{
    orderCapacity *= 2;
    Order* newOrders = new Order[orderCapacity];

    for (int i = 0; i < orderCount; i++)
    {
        newOrders[i] = orders[i];
    }

    delete[] orders;
    orders = newOrders;
}

int CommandHandler::findRestaurantIndexById(int restaurantId) const
{
    for (int i = 0; i < restaurantCount; i++)
    {
        if (restaurants[i].getRestaurantId() == restaurantId)
        {
            return i;
        }
    }
    return -1;
}

int CommandHandler::findOrderIndexById(int orderId) const
{
    for (int i = 0; i < orderCount; i++)
    {
        if (orders[i].getOrderId() == orderId)
        {
            return i;
        }
    }
    return -1;
}

MenuItem CommandHandler::findMenuItemInRestaurant(int restaurantId, int itemId, bool& found) const
{
    found = false;

    int restaurantIndex = findRestaurantIndexById(restaurantId);
    if (restaurantIndex == -1)
    {
        return MenuItem();
    }

    int menuIndex = restaurants[restaurantIndex].findMenuItemIndexById(itemId);
    if (menuIndex == -1)
    {
        return MenuItem();
    }

    found = true;
    return restaurants[restaurantIndex].getMenuItemAt(menuIndex);
}

void CommandHandler::start()
{
    string line;
    bool running = true;

    cout << "Food Delivery CLI Started" << endl;
    cout << "Type 'help' to see commands." << endl;

    while (running)
    {
        cout << ">> ";
        getline(cin, line);

        if (line.empty())
        {
            continue;
        }

        running = processCommand(line);
    }
}

bool CommandHandler::processCommand(string line)
{
    stringstream ss(line);
    string command;
    ss >> command;

    if (command == "help")
    {
        cout << "Available commands:" << endl;
        cout << "help" << endl;
        cout << "show_restaurants" << endl;
        cout << "show_menu <restaurantId>" << endl;
        cout << "add_to_cart <restaurantId> <itemId> <quantity>" << endl;
        cout << "view_cart" << endl;
        cout << "clear_cart" << endl;
        cout << "place_order <cash/card>" << endl;
        cout << "track_order <orderId>" << endl;
        cout << "show_orders" << endl;
        cout << "update_order_status <orderId> <placed/confirmed/preparing/out/delivered/cancelled>" << endl;
        cout << "show_delivery_agents" << endl;
        cout << "assign_delivery_agent <orderId> <agentId>" << endl;
        cout << "exit" << endl;
    }
    else if (command == "show_restaurants")
    {
        if (restaurantCount == 0)
        {
            cout << "No restaurants available." << endl;
            return true;
        }

        for (int i = 0; i < restaurantCount; i++)
        {
            restaurants[i].displayRestaurant();
            cout << "------------------------" << endl;
        }
    }
    else if (command == "show_menu")
    {
        int restaurantId;
        ss >> restaurantId;

        if (ss.fail())
        {
            cout << "Please provide a valid restaurant ID." << endl;
            return true;
        }

        int index = findRestaurantIndexById(restaurantId);

        if (index == -1)
        {
            cout << "Restaurant not found." << endl;
            return true;
        }

        restaurants[index].displayMenu();
    }
    else if (command == "add_to_cart")
    {
        int restaurantId, itemId, quantity;
        ss >> restaurantId >> itemId >> quantity;

        if (ss.fail())
        {
            cout << "Usage: add_to_cart <restaurantId> <itemId> <quantity>" << endl;
            return true;
        }

        int restaurantIndex = findRestaurantIndexById(restaurantId);

        if (restaurantIndex == -1)
        {
            cout << "Restaurant not found." << endl;
            return true;
        }

        if (!cart.isEmpty() && currentCartRestaurantId != restaurantId)
        {
            cout << "Cart already contains items from another restaurant." << endl;
            cout << "Clear cart first before adding from a different restaurant." << endl;
            return true;
        }

        bool found = false;
        MenuItem item = findMenuItemInRestaurant(restaurantId, itemId, found);

        if (!found)
        {
            cout << "Menu item not found." << endl;
            return true;
        }

        cart.addItem(item, quantity);
        currentCartRestaurantId = restaurantId;
        cout << "Item added to cart." << endl;
    }
    else if (command == "assign_delivery_agent")
    {
        int orderId, agentId;
        ss >> orderId >> agentId;

        if (ss.fail())
        {
            cout << "Usage: assign_delivery_agent <orderId> <agentId>" << endl;
            return true;
        }

        int index = findOrderIndexById(orderId);

        if (index == -1)
        {
            cout << "Order not found." << endl;
            return true;
        }

        if (orders[index].getDeliveryAgentId() != -1)
        {
            cout << "This order already has a delivery agent assigned." << endl;
            return true;
        }

        if (!fileManager.isDeliveryAgentAvailable(agentId))
        {
            cout << "Delivery agent is not available or does not exist." << endl;
            return true;
        }

        orders[index].setDeliveryAgentId(agentId);
        fileManager.updateDeliveryAgentAvailability(agentId, false);

        cout << "Delivery agent assigned successfully." << endl;
    }
    else if (command == "show_delivery_agents")
    {
        fileManager.showDeliveryAgents();
    }
    else if (command == "view_cart")
    {
        cart.displayCart();
    }
    else if (command == "clear_cart")
    {
        cart.clearCart();
        currentCartRestaurantId = -1;
        cout << "Cart cleared." << endl;
    }
    else if (command == "place_order")
    {
        string paymentText;
        ss >> paymentText;

        if (ss.fail())
        {
            cout << "Usage: place_order <cash/card>" << endl;
            return true;
        }

        if (cart.isEmpty())
        {
            cout << "Cart is empty. Add items before placing an order." << endl;
            return true;
        }

        PaymentType paymentType;

        if (paymentText == "cash")
            paymentType = PaymentType::CASH;
        else if (paymentText == "card")
            paymentType = PaymentType::CARD;

        else
        {
            cout << "Invalid payment type. Use cash or card." << endl;
            return true;
        }

        double total = cart.calculateTotal();

        Order newOrder(nextOrderId, currentCustomerId, currentCartRestaurantId, total, paymentType);

        Payment payment(nextPaymentId, nextOrderId, total, paymentType);
        payment.processPayment();
        newOrder.setPaymentStatus(payment.getPaymentStatus());

        if (orderCount == orderCapacity)
        {
            resizeOrders();
        }

        orders[orderCount] = newOrder;
        fileManager.saveOrder(newOrder);

        cout << "Order placed successfully." << endl;
        cout << "Your order ID is: " << nextOrderId << endl;

        orderCount++;
        nextOrderId++;
        nextPaymentId++;

        cart.clearCart();
        currentCartRestaurantId = -1;
    }
    else if (command == "track_order")
    {
        int orderId;
        ss >> orderId;

        if (ss.fail())
        {
            cout << "Usage: track_order <orderId>" << endl;
            return true;
        }

        int index = findOrderIndexById(orderId);

        if (index == -1)
        {
            cout << "Order not found." << endl;
            return true;
        }

        orders[index].displayOrder();
    }
    else if (command == "show_orders")
    {
        if (orderCount == 0)
        {
            cout << "No orders placed yet." << endl;
            return true;
        }

        for (int i = 0; i < orderCount; i++)
        {
            orders[i].displayOrder();
            cout << "------------------------" << endl;
        }
    }
    else if (command == "update_order_status")
    {
        int orderId;
        string statusText;

        ss >> orderId >> statusText;

        if (ss.fail())
        {
            cout << "Usage: update_order_status <orderId> <placed/confirmed/preparing/out/delivered/cancelled>" << endl;
            return true;
        }

        int index = findOrderIndexById(orderId);

        if (index == -1)
        {
            cout << "Order not found." << endl;
            return true;
        }

        if (statusText == "placed")
            orders[index].setStatus(OrderStatus::PLACED);
        else if (statusText == "confirmed")
            orders[index].setStatus(OrderStatus::CONFIRMED);
        else if (statusText == "preparing")
            orders[index].setStatus(OrderStatus::PREPARING);
        else if (statusText == "out")
            orders[index].setStatus(OrderStatus::OUT_FOR_DELIVERY);
        else if (statusText == "delivered")
        {
            orders[index].setStatus(OrderStatus::DELIVERED);

            int agentId = orders[index].getDeliveryAgentId();
            if (agentId != -1)
            {
                fileManager.updateDeliveryAgentAvailability(agentId, true);
            }
        }
        else if (statusText == "cancelled")
        {
            orders[index].setStatus(OrderStatus::CANCELLED);

            int agentId = orders[index].getDeliveryAgentId();
            if (agentId != -1)
            {
                fileManager.updateDeliveryAgentAvailability(agentId, true);
            }
        }
        else
        {
            cout << "Invalid status." << endl;
            return true;
        }

        cout << "Order status updated." << endl;
    }
    else if (command == "exit")
    {
        cout << "Exiting program..." << endl;
        return false;
    }
    else
    {
        cout << "Unknown command." << endl;
    }

    return true;
}