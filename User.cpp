#include "User.h"

// Default constructor
User::User()
{
    userId = 0;
    name = "";
    username = "";
    password = "";
    address = "";
    phone = "";
    role = UserRole::CUSTOMER;
}

// Parameterized constructor
User::User(int userId, string name, string username, string password, string address, string phone, UserRole role)
{
    this->userId = userId;
    this->name = name;
    this->username = username;
    this->password = password;
    this->address = address;
    this->phone = phone;
    this->role = role;
}

User::~User()
{
}

int User::getUserId() const
{
    return userId;
}

string User::getName() const
{
    return name;
}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

string User::getAddress() const
{
    return address;
}

string User::getPhone() const
{
    return phone;
}

UserRole User::getRole() const
{
    return role;
}

void User::setName(string name)
{
    this->name = name;
}

void User::setUsername(string username)
{
    this->username = username;
}

void User::setPassword(string password)
{
    this->password = password;
}

void User::setAddress(string address)
{
    this->address = address;
}

void User::setPhone(string phone)
{
    this->phone = phone;
}

// Displays common user information
void User::showProfile() const
{
    cout << "User ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Username: " << username << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phone << endl;
}