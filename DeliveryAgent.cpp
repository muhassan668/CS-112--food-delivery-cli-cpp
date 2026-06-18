#include "DeliveryAgent.h"

// Default constructor
DeliveryAgent::DeliveryAgent() : User()
{
    role = UserRole::DELIVERY_AGENT;
    vehicleType = "";
    isAvailable = true;
}

// Parameterized constructor
DeliveryAgent::DeliveryAgent(int userId, string name, string username, string password, string address, string phone, string vehicleType)
    : User(userId, name, username, password, address, phone, UserRole::DELIVERY_AGENT)
{
    this->vehicleType = vehicleType;
    isAvailable = true;
}

void DeliveryAgent::setVehicleType(string vehicleType)
{
    this->vehicleType = vehicleType;
}

void DeliveryAgent::setAvailability(bool isAvailable)
{
    this->isAvailable = isAvailable;
}

string DeliveryAgent::getVehicleType() const
{
    return vehicleType;
}

bool DeliveryAgent::getAvailability() const
{
    return isAvailable;
}

// Displays delivery agent details
void DeliveryAgent::showProfile() const
{
    cout << "----- Delivery Agent Profile -----" << endl;
    User::showProfile();
    cout << "Role: Delivery Agent" << endl;
    cout << "Vehicle Type: " << vehicleType << endl;
    cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
}