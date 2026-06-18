#ifndef CART_H
#define CART_H

#include <iostream>
#include "MenuItem.h"
using namespace std;

class Cart
{
private:
    struct CartEntry
    {
        MenuItem item;
        int quantity;
    };

    CartEntry* entries;
    int itemCount;
    int capacity;

    void resizeCart();

public:
    Cart();
    Cart(const Cart& other);
    Cart& operator=(const Cart& other);
    ~Cart();

    void addItem(const MenuItem& item, int quantity);
    void removeItem(int itemId);
    void updateQuantity(int itemId, int newQuantity);

    int findItemIndexById(int itemId) const;
    int getItemCount() const;
    bool isEmpty() const;

    double calculateTotal() const;
    void displayCart() const;
    void clearCart();
};

#endif