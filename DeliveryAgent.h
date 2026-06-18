#ifndef DELIVERYAGENT_H
#define DELIVERYAGENT_H

#include "User.h"

// Delivery agent class derived from User
class DeliveryAgent : public User
{
private:
    string vehicleType;
    bool isAvailable;

public:
    DeliveryAgent();
    DeliveryAgent(int userId, string name, string username, string password, string address, string phone, string vehicleType);

    void setVehicleType(string vehicleType);
    void setAvailability(bool isAvailable);

    string getVehicleType() const;
    bool getAvailability() const;

    void showProfile() const override;
};

#endif