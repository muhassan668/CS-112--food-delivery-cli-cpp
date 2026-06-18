#include "Admin.h"

// Default constructor
Admin::Admin() : User()
{
    role = UserRole::ADMIN;
}

// Parameterized constructor
Admin::Admin(int userId, string name, string username, string password, string address, string phone)
    : User(userId, name, username, password, address, phone, UserRole::ADMIN)
{
}

// Displays admin details
void Admin::showProfile() const
{
    cout << "----- Admin Profile -----" << endl;
    User::showProfile();
    cout << "Role: Admin" << endl;
}