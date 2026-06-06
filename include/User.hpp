#ifndef USER_HPP
#define USER_HPP

#include "CryptoManager.hpp"
#include <string>
#include <stdexcept>
#include <memory>

class User {
public:
    User(int ID, std::string Username, std::unique_ptr<CryptoManager> Manager): id(ID), username(Username), manager(std::move(Manager)) {}

    Bytes encryptData(const std::string& msg) {
        if (!manager) throw std::runtime_error("ERROR: No crypto manager!");
        return manager->encrypt(msg);
    }

    std::string decryptData(const Bytes& msg) {
        if (!manager) throw std::runtime_error("ERROR: No crypto manager!");
        return manager->decrypt(msg);
    }

    void generateUserKey(size_t length) {
        if (!manager) throw std::runtime_error("ERROR: No crypto manager!");
        manager->setKey(manager->generateKeys(length));
    }

    void setUserKey(const Bytes& key) {
        if (!manager) throw std::runtime_error("ERROR: No crypto manager!");
        manager->setKey(key);
    }

    int getId() const {
        return id;
    }
    
private:
    int id;
    std::string username;
    std::unique_ptr<CryptoManager> manager;
};

#endif // USER_HPP