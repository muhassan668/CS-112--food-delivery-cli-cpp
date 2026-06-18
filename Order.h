#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "Enums.h"
using namespace std;

class Order
{
private:
    int orderId;
    int customerId;
    int restaurantId;
    double totalAmount;
    OrderStatus status;
    PaymentType paymentType;
    PaymentStatus paymentStatus;
    int deliveryAgentId;

public:
    Order();
    Order(int orderId, int customerId, int restaurantId, double totalAmount, PaymentType paymentType);

    int getOrderId() const;
    int getCustomerId() const;
    int getRestaurantId() const;
    double getTotalAmount() const;
    OrderStatus getStatus() const;
    PaymentType getPaymentType() const;
    PaymentStatus getPaymentStatus() const;
    int getDeliveryAgentId() const;

    void setStatus(OrderStatus status);
    void setPaymentStatus(PaymentStatus paymentStatus);
    void setDeliveryAgentId(int deliveryAgentId);

    void displayOrder() const;
};

#endif