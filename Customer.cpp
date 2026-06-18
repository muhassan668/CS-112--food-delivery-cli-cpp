#include "Customer.h"

// Default constructor
Customer::Customer() : User()
{
    role = UserRole::CUSTOMER;
    capacity = 5;
    orderCount = 0;
    orderHistory = new int[capacity];
}

// Parameterized constructor
Customer::Customer(int userId, string name, string username, string password, string address, string phone)
    : User(userId, name, username, password, address, phone, UserRole::CUSTOMER)
{
    capacity = 5;
    orderCount = 0;
    orderHistory = new int[capacity];
}

// Copy constructor for deep copy
Customer::Customer(const Customer& other) : User(other)
{
    capacity = other.capacity;
    orderCount = other.orderCount;
    orderHistory = new int[capacity];

    for (int i = 0; i < orderCount; i++)
    {
        orderHistory[i] = other.orderHistory[i];
    }
}

// Assignment operator for deep copy
Customer& Customer::operator=(const Customer& other)
{
    if (this != &other)
    {
        userId = other.userId;
        name = other.name;
        username = other.username;
        password = other.password;
        address = other.address;
        phone = other.phone;
        role = other.role;

        delete[] orderHistory;

        capacity = other.capacity;
        orderCount = other.orderCount;
        orderHistory = new int[capacity];

        for (int i = 0; i < orderCount; i++)
        {
            orderHistory[i] = other.orderHistory[i];
        }
    }
    return *this;
}

// Destructor to release dynamic memory
Customer::~Customer()
{
    delete[] orderHistory;
}

// Doubles the array size when full
void Customer::resizeArray()
{
    capacity *= 2;
    int* newArray = new int[capacity];

    for (int i = 0; i < orderCount; i++)
    {
        newArray[i] = orderHistory[i];
    }

    delete[] orderHistory;
    orderHistory = newArray;
}

// Adds a new order id to customer history
void Customer::addOrderToHistory(int orderId)
{
    if (orderCount == capacity)
    {
        resizeArray();
    }

    orderHistory[orderCount] = orderId;
    orderCount++;
}

int Customer::getOrderCount() const
{
    return orderCount;
}

// Returns the order id at a given index
int Customer::getOrderAt(int index) const
{
    if (index >= 0 && index < orderCount)
    {
        return orderHistory[index];
    }
    return -1;
}

// Shows customer details
void Customer::showProfile() const
{
    cout << "----- Customer Profile -----" << endl;
    User::showProfile();
    cout << "Role: Customer" << endl;
    cout << "Total Orders: " << orderCount << endl;
}