#include "FileManager.h"
#include <sstream>

UserRole FileManager::stringToUserRole(const string& roleText)
{
    if (roleText == "ADMIN")
        return UserRole::ADMIN;
    else if (roleText == "DELIVERY_AGENT")
        return UserRole::DELIVERY_AGENT;
    else
        return UserRole::CUSTOMER;
}

OrderStatus FileManager::stringToOrderStatus(const string& statusText)
{
    if (statusText == "CONFIRMED")
        return OrderStatus::CONFIRMED;
    else if (statusText == "PREPARING")
        return OrderStatus::PREPARING;
    else if (statusText == "OUT_FOR_DELIVERY")
        return OrderStatus::OUT_FOR_DELIVERY;
    else if (statusText == "DELIVERED")
        return OrderStatus::DELIVERED;
    else if (statusText == "CANCELLED")
        return OrderStatus::CANCELLED;
    else
        return OrderStatus::PLACED;
}

PaymentType FileManager::stringToPaymentType(const string& paymentTypeText)
{
    if (paymentTypeText == "CARD")
        return PaymentType::CARD;
    return PaymentType::CASH;
}

PaymentStatus FileManager::stringToPaymentStatus(const string& paymentStatusText)
{
    if (paymentStatusText == "COMPLETED")
        return PaymentStatus::COMPLETED;
    else if (paymentStatusText == "FAILED")
        return PaymentStatus::FAILED;
    return PaymentStatus::PENDING;
}

void FileManager::saveUser(const User& user)
{
    ofstream fout("users.txt", ios::app);

    if (!fout)
    {
        cout << "Error opening users.txt" << endl;
        return;
    }

    string roleText;

    if (user.getRole() == UserRole::CUSTOMER)
        roleText = "CUSTOMER";
    else if (user.getRole() == UserRole::ADMIN)
        roleText = "ADMIN";
    else
        roleText = "DELIVERY_AGENT";

    fout << user.getUserId() << "|"
         << user.getName() << "|"
         << user.getUsername() << "|"
         << user.getPassword() << "|"
         << user.getAddress() << "|"
         << user.getPhone() << "|"
         << roleText << endl;

    fout.close();
}

void FileManager::saveDeliveryAgent(const DeliveryAgent& agent)
{
    ofstream fout("delivery_agents.txt", ios::app);

    if (!fout)
    {
        cout << "Error opening delivery_agents.txt" << endl;
        return;
    }

    fout << agent.getUserId() << "|"
         << agent.getName() << "|"
         << agent.getUsername() << "|"
         << agent.getPassword() << "|"
         << agent.getAddress() << "|"
         << agent.getPhone() << "|"
         << agent.getVehicleType() << "|"
         << agent.getAvailability() << endl;

    fout.close();
}

void FileManager::saveRestaurant(const Restaurant& restaurant)
{
    ofstream fout("restaurants.txt", ios::app);

    if (!fout)
    {
        cout << "Error opening restaurants.txt" << endl;
        return;
    }

    fout << restaurant.getRestaurantId() << "|"
         << restaurant.getRestaurantName() << "|"
         << restaurant.getLocation() << endl;

    fout.close();
}

void FileManager::saveOrder(const Order& order)
{
    ofstream fout("orders.txt", ios::app);

    if (!fout)
    {
        cout << "Error opening orders.txt" << endl;
        return;
    }

    string statusText;
    string paymentTypeText;
    string paymentStatusText;

    if (order.getStatus() == OrderStatus::PLACED)
        statusText = "PLACED";
    else if (order.getStatus() == OrderStatus::CONFIRMED)
        statusText = "CONFIRMED";
    else if (order.getStatus() == OrderStatus::PREPARING)
        statusText = "PREPARING";
    else if (order.getStatus() == OrderStatus::OUT_FOR_DELIVERY)
        statusText = "OUT_FOR_DELIVERY";
    else if (order.getStatus() == OrderStatus::DELIVERED)
        statusText = "DELIVERED";
    else
        statusText = "CANCELLED";

    if (order.getPaymentType() == PaymentType::CASH)
        paymentTypeText = "CASH";
    else
        paymentTypeText = "CARD";

    if (order.getPaymentStatus() == PaymentStatus::PENDING)
        paymentStatusText = "PENDING";
    else if (order.getPaymentStatus() == PaymentStatus::COMPLETED)
        paymentStatusText = "COMPLETED";
    else
        paymentStatusText = "FAILED";

    fout << order.getOrderId() << "|"
         << order.getCustomerId() << "|"
         << order.getRestaurantId() << "|"
         << order.getTotalAmount() << "|"
         << statusText << "|"
         << paymentTypeText << "|"
         << paymentStatusText << "|"
         << order.getDeliveryAgentId() << endl;

    fout.close();
}

int FileManager::loadRestaurants(Restaurant*& restaurants, int& capacity)
{
    ifstream fin("restaurants.txt");

    if (!fin)
    {
        cout << "Error opening restaurants.txt" << endl;
        return 0;
    }

    capacity = 10;
    restaurants = new Restaurant[capacity];
    int count = 0;

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string part;

        string idText, name, location;

        getline(ss, idText, '|');
        getline(ss, name, '|');
        getline(ss, location);

        int restaurantId = stoi(idText);

        if (count == capacity)
        {
            capacity *= 2;
            Restaurant* newRestaurants = new Restaurant[capacity];

            for (int i = 0; i < count; i++)
            {
                newRestaurants[i] = restaurants[i];
            }

            delete[] restaurants;
            restaurants = newRestaurants;
        }

        restaurants[count] = Restaurant(restaurantId, name, location);
        count++;
    }

    fin.close();
    return count;
}

void FileManager::loadMenuItems(Restaurant* restaurants, int restaurantCount)
{
    ifstream fin("menu_items.txt");

    if (!fin)
    {
        cout << "Error opening menu_items.txt" << endl;
        return;
    }

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string restaurantIdText, itemIdText, itemName, priceText, category, availableText;

        getline(ss, restaurantIdText, '|');
        getline(ss, itemIdText, '|');
        getline(ss, itemName, '|');
        getline(ss, priceText, '|');
        getline(ss, category, '|');
        getline(ss, availableText);

        int restaurantId = stoi(restaurantIdText);
        int itemId = stoi(itemIdText);
        double price = stod(priceText);
        bool isAvailable = (stoi(availableText) == 1);

        MenuItem item(itemId, itemName, price, category, isAvailable);

        for (int i = 0; i < restaurantCount; i++)
        {
            if (restaurants[i].getRestaurantId() == restaurantId)
            {
                restaurants[i].addMenuItem(item);
                break;
            }
        }
    }

    fin.close();
}

int FileManager::loadOrders(Order*& orders, int& capacity)
{
    ifstream fin("orders.txt");

    if (!fin)
    {
        capacity = 10;
        orders = new Order[capacity];
        return 0;
    }

    capacity = 10;
    orders = new Order[capacity];
    int count = 0;

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string orderIdText, customerIdText, restaurantIdText, totalAmountText;
        string statusText, paymentTypeText, paymentStatusText, deliveryAgentIdText;

        getline(ss, orderIdText, '|');
        getline(ss, customerIdText, '|');
        getline(ss, restaurantIdText, '|');
        getline(ss, totalAmountText, '|');
        getline(ss, statusText, '|');
        getline(ss, paymentTypeText, '|');
        getline(ss, paymentStatusText, '|');
        getline(ss, deliveryAgentIdText);

        int orderId = stoi(orderIdText);
        int customerId = stoi(customerIdText);
        int restaurantId = stoi(restaurantIdText);
        double totalAmount = stod(totalAmountText);
        int deliveryAgentId = stoi(deliveryAgentIdText);

        PaymentType paymentType = stringToPaymentType(paymentTypeText);
        PaymentStatus paymentStatus = stringToPaymentStatus(paymentStatusText);
        OrderStatus orderStatus = stringToOrderStatus(statusText);

        if (count == capacity)
        {
            capacity *= 2;
            Order* newOrders = new Order[capacity];

            for (int i = 0; i < count; i++)
            {
                newOrders[i] = orders[i];
            }

            delete[] orders;
            orders = newOrders;
        }

        orders[count] = Order(orderId, customerId, restaurantId, totalAmount, paymentType);
        orders[count].setStatus(orderStatus);
        orders[count].setPaymentStatus(paymentStatus);
        orders[count].setDeliveryAgentId(deliveryAgentId);
        count++;
    }
    

    fin.close();
    return count;
}


void FileManager::showDeliveryAgents()
{
    ifstream fin("delivery_agents.txt");

    if (!fin)
    {
        cout << "Error opening delivery_agents.txt" << endl;
        return;
    }

    string line;
    bool foundAny = false;

    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string idText, name, username, password, address, phone, vehicleType, availableText;

        getline(ss, idText, '|');
        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, address, '|');
        getline(ss, phone, '|');
        getline(ss, vehicleType, '|');
        getline(ss, availableText);

        cout << "Agent ID: " << idText << endl;
        cout << "Name: " << name << endl;
        cout << "Username: " << username << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "Availability: " << (availableText == "1" ? "Available" : "Not Available") << endl;
        cout << "------------------------" << endl;

        foundAny = true;
    }

    if (!foundAny)
    {
        cout << "No delivery agents found." << endl;
    }

    fin.close();
}
bool FileManager::isDeliveryAgentAvailable(int agentId)
{
    ifstream fin("delivery_agents.txt");

    if (!fin)
    {
        cout << "Error opening delivery_agents.txt" << endl;
        return false;
    }

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string idText, name, username, password, address, phone, vehicleType, availableText;

        getline(ss, idText, '|');
        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, address, '|');
        getline(ss, phone, '|');
        getline(ss, vehicleType, '|');
        getline(ss, availableText);

        if (stoi(idText) == agentId)
        {
            fin.close();
            return (availableText == "1");
        }
    }

    fin.close();
    return false;
}

void FileManager::updateDeliveryAgentAvailability(int agentId, bool isAvailable)
{
    ifstream fin("delivery_agents.txt");

    if (!fin)
    {
        cout << "Error opening delivery_agents.txt" << endl;
        return;
    }

    string allData = "";
    string line;

    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string idText, name, username, password, address, phone, vehicleType, availableText;

        getline(ss, idText, '|');
        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, address, '|');
        getline(ss, phone, '|');
        getline(ss, vehicleType, '|');
        getline(ss, availableText);

        if (stoi(idText) == agentId)
        {
            availableText = isAvailable ? "1" : "0";
        }

        allData += idText + "|" + name + "|" + username + "|" + password + "|" +
                   address + "|" + phone + "|" + vehicleType + "|" + availableText + "\n";
    }

    fin.close();

    ofstream fout("delivery_agents.txt");

    if (!fout)
    {
        cout << "Error writing to delivery_agents.txt" << endl;
        return;
    }

    fout << allData;
    fout.close();
}