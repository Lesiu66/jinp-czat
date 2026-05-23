#ifndef USER_HPP
#define USER_HPP

#include "CryptoManager.hpp"
#include <string>

class User {
public:
    User(int ID, std::string Username): id(ID), username(Username) {}
private:
    int id;
    std::string username;
    CryptoManager* manager;
};

#endif // USER_HPP