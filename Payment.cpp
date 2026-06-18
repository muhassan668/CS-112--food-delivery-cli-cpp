#include "Payment.h"

// Default constructor
Payment::Payment()
{
    paymentId = 0;
    orderId = 0;
    amount = 0.0;
    paymentType = PaymentType::CASH;
    paymentStatus = PaymentStatus::PENDING;
}

// Parameterized constructor
Payment::Payment(int paymentId, int orderId, double amount, PaymentType paymentType)
{
    this->paymentId = paymentId;
    this->orderId = orderId;
    this->amount = amount;
    this->paymentType = paymentType;
    paymentStatus = PaymentStatus::PENDING;
}

int Payment::getPaymentId() const
{
    return paymentId;
}

int Payment::getOrderId() const
{
    return orderId;
}

double Payment::getAmount() const
{
    return amount;
}

PaymentType Payment::getPaymentType() const
{
    return paymentType;
}

PaymentStatus Payment::getPaymentStatus() const
{
    return paymentStatus;
}

void Payment::setAmount(double amount)
{
    this->amount = amount;
}

void Payment::setPaymentStatus(PaymentStatus paymentStatus)
{
    this->paymentStatus = paymentStatus;
}

// Simulates payment processing
void Payment::processPayment()
{
    if (amount <= 0)
    {
        paymentStatus = PaymentStatus::FAILED;
        cout << "Payment failed." << endl;
    }
    else
    {
        paymentStatus = PaymentStatus::COMPLETED;
        cout << "Payment processed successfully." << endl;
    }
}

// Displays payment details
void Payment::displayPayment() const
{
    cout << "Payment ID: " << paymentId << endl;
    cout << "Order ID: " << orderId << endl;
    cout << "Amount: " << amount << endl;

    cout << "Payment Type: ";
    if (paymentType == PaymentType::CASH)
        cout << "Cash" << endl;
    else if (paymentType == PaymentType::CARD)
        cout << "Card" << endl;

    cout << "Payment Status: ";
    if (paymentStatus == PaymentStatus::PENDING)
        cout << "Pending" << endl;
    else if (paymentStatus == PaymentStatus::COMPLETED)
        cout << "Completed" << endl;
    else if (paymentStatus == PaymentStatus::FAILED)
        cout << "Failed" << endl;
}