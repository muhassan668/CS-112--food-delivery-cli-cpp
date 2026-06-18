#include "Order.h"

// Default constructor
Order::Order()
{
    orderId = 0;
    customerId = 0;
    restaurantId = 0;
    totalAmount = 0.0;
    status = OrderStatus::PLACED;
    paymentType = PaymentType::CASH;
    paymentStatus = PaymentStatus::PENDING;
    deliveryAgentId = -1;
}

// Parameterized constructor
Order::Order(int orderId, int customerId, int restaurantId, double totalAmount, PaymentType paymentType)
{
    this->orderId = orderId;
    this->customerId = customerId;
    this->restaurantId = restaurantId;
    this->totalAmount = totalAmount;
    this->paymentType = paymentType;

    status = OrderStatus::PLACED;
    paymentStatus = PaymentStatus::PENDING;
    deliveryAgentId = -1;
}

int Order::getOrderId() const
{
    return orderId;
}

int Order::getCustomerId() const
{
    return customerId;
}

int Order::getRestaurantId() const
{
    return restaurantId;
}

double Order::getTotalAmount() const
{
    return totalAmount;
}

OrderStatus Order::getStatus() const
{
    return status;
}

PaymentType Order::getPaymentType() const
{
    return paymentType;
}

PaymentStatus Order::getPaymentStatus() const
{
    return paymentStatus;
}

int Order::getDeliveryAgentId() const
{
    return deliveryAgentId;
}

void Order::setStatus(OrderStatus status)
{
    this->status = status;
}

void Order::setPaymentStatus(PaymentStatus paymentStatus)
{
    this->paymentStatus = paymentStatus;
}

void Order::setDeliveryAgentId(int deliveryAgentId)
{
    this->deliveryAgentId = deliveryAgentId;
}

void Order::displayOrder() const
{
    cout << "Order ID: " << orderId << endl;
    cout << "Customer ID: " << customerId << endl;
    cout << "Restaurant ID: " << restaurantId << endl;
    cout << "Total Amount: " << totalAmount << endl;

    cout << "Order Status: ";
    if (status == OrderStatus::PLACED) cout << "Placed" << endl;
    else if (status == OrderStatus::CONFIRMED) cout << "Confirmed" << endl;
    else if (status == OrderStatus::PREPARING) cout << "Preparing" << endl;
    else if (status == OrderStatus::OUT_FOR_DELIVERY) cout << "Out for Delivery" << endl;
    else if (status == OrderStatus::DELIVERED) cout << "Delivered" << endl;
    else if (status == OrderStatus::CANCELLED) cout << "Cancelled" << endl;

    cout << "Payment Type: ";
    if (paymentType == PaymentType::CASH) cout << "Cash" << endl;
    else if (paymentType == PaymentType::CARD) cout << "Card" << endl;

    cout << "Payment Status: ";
    if (paymentStatus == PaymentStatus::PENDING) cout << "Pending" << endl;
    else if (paymentStatus == PaymentStatus::COMPLETED) cout << "Completed" << endl;
    else if (paymentStatus == PaymentStatus::FAILED) cout << "Failed" << endl;

    cout << "Delivery Agent ID: " << deliveryAgentId << endl;
}