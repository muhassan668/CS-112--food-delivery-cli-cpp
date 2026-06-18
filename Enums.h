#ifndef ENUMS_H
#define ENUMS_H

// Different roles in the system
enum class UserRole
{
    CUSTOMER,
    ADMIN,
    DELIVERY_AGENT
};

// Different stages of an order
enum class OrderStatus
{
    PLACED,
    CONFIRMED,
    PREPARING,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
};

// Payment result status
enum class PaymentStatus
{
    PENDING,
    COMPLETED,
    FAILED
};

// Payment methods available in the system
enum class PaymentType
{
    CASH,
    CARD
};

#endif