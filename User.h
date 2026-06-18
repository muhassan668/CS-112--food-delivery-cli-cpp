#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Enums.h"

using namespace std;

// Base class for all users in the system
class User
{
protected:
    int userId;
    string name;
    string username;
    string password;
    string address;
    string phone;
    UserRole role;

public:
    User();
    User(int userId, string name, string username, string password, string address, string phone, UserRole role);

    virtual ~User();

    int getUserId() const;
    string getName() const;
    string getUsername() const;
    string getPassword() const;
    string getAddress() const;
    string getPhone() const;
    UserRole getRole() const;

    void setName(string name);
    void setUsername(string username);
    void setPassword(string password);
    void setAddress(string address);
    void setPhone(string phone);

    // Virtual so child classes can show their own profile format
    virtual void showProfile() const;
};

#endif