#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

// Admin class derived from User
class Admin : public User
{
public:
    Admin();
    Admin(int userId, string name, string username, string password, string address, string phone);

    void showProfile() const override;
};

#endif