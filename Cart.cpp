#include "Cart.h"

// Default constructor
Cart::Cart()
{
    capacity = 5;
    itemCount = 0;
    entries = new CartEntry[capacity];
}

// Copy constructor
Cart::Cart(const Cart& other)
{
    capacity = other.capacity;
    itemCount = other.itemCount;
    entries = new CartEntry[capacity];

    for (int i = 0; i < itemCount; i++)
    {
        entries[i] = other.entries[i];
    }
}

// Assignment operator
Cart& Cart::operator=(const Cart& other)
{
    if (this != &other)
    {
        delete[] entries;

        capacity = other.capacity;
        itemCount = other.itemCount;
        entries = new CartEntry[capacity];

        for (int i = 0; i < itemCount; i++)
        {
            entries[i] = other.entries[i];
        }
    }
    return *this;
}

// Destructor
Cart::~Cart()
{
    delete[] entries;
}

// Resizes the cart when it becomes full
void Cart::resizeCart()
{
    capacity = capacity * 2;
    CartEntry* newEntries = new CartEntry[capacity];

    for (int i = 0; i < itemCount; i++)
    {
        newEntries[i] = entries[i];
    }

    delete[] entries;
    entries = newEntries;
}

// Searches item by id
int Cart::findItemIndexById(int itemId) const
{
    for (int i = 0; i < itemCount; i++)
    {
        if (entries[i].item.getItemId() == itemId)
        {
            return i;
        }
    }
    return -1;
}

// Adds item to cart or increases quantity if item already exists
void Cart::addItem(const MenuItem& item, int quantity)
{
    if (quantity <= 0)
    {
        cout << "Invalid quantity." << endl;
        return;
    }

    if (!item.getIsAvailable())
    {
        cout << "Item is not available." << endl;
        return;
    }

    int index = findItemIndexById(item.getItemId());

    if (index != -1)
    {
        entries[index].quantity += quantity;
        return;
    }

    if (itemCount == capacity)
    {
        resizeCart();
    }

    entries[itemCount].item = item;
    entries[itemCount].quantity = quantity;
    itemCount++;
}

// Removes an item from cart
void Cart::removeItem(int itemId)
{
    int index = findItemIndexById(itemId);

    if (index == -1)
    {
        cout << "Item not found in cart." << endl;
        return;
    }

    for (int i = index; i < itemCount - 1; i++)
    {
        entries[i] = entries[i + 1];
    }

    itemCount--;
    cout << "Item removed from cart." << endl;
}

// Updates quantity of an item
void Cart::updateQuantity(int itemId, int newQuantity)
{
    int index = findItemIndexById(itemId);

    if (index == -1)
    {
        cout << "Item not found in cart." << endl;
        return;
    }

    if (newQuantity <= 0)
    {
        removeItem(itemId);
        return;
    }

    entries[index].quantity = newQuantity;
    cout << "Quantity updated." << endl;
}

int Cart::getItemCount() const
{
    return itemCount;
}

bool Cart::isEmpty() const
{
    return itemCount == 0;
}

// Calculates total bill
double Cart::calculateTotal() const
{
    double total = 0.0;

    for (int i = 0; i < itemCount; i++)
    {
        total += entries[i].item.getPrice() * entries[i].quantity;
    }

    return total;
}

// Displays all items in the cart
void Cart::displayCart() const
{
    if (isEmpty())
    {
        cout << "Cart is empty." << endl;
        return;
    }

    cout << "----- Cart Items -----" << endl;

    for (int i = 0; i < itemCount; i++)
    {
        cout << "Item ID: " << entries[i].item.getItemId() << endl;
        cout << "Name: " << entries[i].item.getItemName() << endl;
        cout << "Price: " << entries[i].item.getPrice() << endl;
        cout << "Quantity: " << entries[i].quantity << endl;
        cout << "Subtotal: " << entries[i].item.getPrice() * entries[i].quantity << endl;
        cout << "----------------------" << endl;
    }

    cout << "Total Bill: " << calculateTotal() << endl;
}

// Clears all items from cart
void Cart::clearCart()
{
    itemCount = 0;
}