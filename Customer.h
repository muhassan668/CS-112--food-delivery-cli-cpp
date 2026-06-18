#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

// Customer class derived from User
class Customer : public User
{
private:
    int* orderHistory;
    int orderCount;
    int capacity;

    // Expands the array when it becomes full
    void resizeArray();

public:
    Customer();
    Customer(int userId, string name, string username, string password, string address, string phone);
    Customer(const Customer& other);
    Customer& operator=(const Customer& other);
    ~Customer();

    void addOrderToHistory(int orderId);
    int getOrderCount() const;
    int getOrderAt(int index) const;

    void showProfile() const override;
};

#endif