#ifndef MESSAGEHISTORY_HPP
#define MESSAGEHISTORY_HPP

#include <vector>
#include "Message.hpp"
#include <iostream>
#include <memory>
#include "CryptoManager.hpp"

class MessageHistory {
public:
    MessageHistory(CryptoManager* cryptoManager) : manager(cryptoManager) {}

    void addMessage(const std::string& msg, int senderId, int receiverId, int64_t timestamp);
    void generateKey(const std::string& password) { manager->setKey(manager->generateKeyFromPassword(password)); }
    std::vector<Message> getHistory();
    void saveToFile(std::ostream& file);
    void loadFromFile(std::istream& file);
    void displayHistory();
private:
    std::vector<Message> history;
    CryptoManager* manager;
};

#endif // MESSAGEHISTORY_HPP