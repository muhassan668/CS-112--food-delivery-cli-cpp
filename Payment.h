#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include "Enums.h"
using namespace std;

class Payment
{
private:
    int paymentId;
    int orderId;
    double amount;
    PaymentType paymentType;
    PaymentStatus paymentStatus;

public:
    Payment();
    Payment(int paymentId, int orderId, double amount, PaymentType paymentType);

    int getPaymentId() const;
    int getOrderId() const;
    double getAmount() const;
    PaymentType getPaymentType() const;
    PaymentStatus getPaymentStatus() const;

    void setAmount(double amount);
    void setPaymentStatus(PaymentStatus paymentStatus);

    void processPayment();
    void displayPayment() const;
};

#endif