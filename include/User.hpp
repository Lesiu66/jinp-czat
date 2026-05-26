#ifndef USER_HPP
#define USER_HPP

#include "CryptoManager.hpp"
#include <string>
#include <stdexcept>

class User {
public:
    User(int ID, std::string Username, CryptoManager* Manager): id(ID), username(Username), manager(std::move(Manager)) {}

    Bytes encryptData(const std::string& msg) {
        if (!manager) throw std::runtime_error("ERROR: No crypto manager!");
        return manager->encrypt(msg);
    }

    std::string decryptData(const Bytes& msg) {
        if (!manager) throw std::runtime_error("ERROR: No crypto manager!");
        return manager->decrypt(msg);
    }

    void generateUserKey() {
        if (!manager) throw std::runtime_error("ERROR: No crypto manager!");
        manager->generateKeys();
    }

private:
    int id;
    std::string username;
    CryptoManager* manager;
};

#endif // USER_HPP