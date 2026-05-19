#ifndef MESSAGEHISTORY_HPP
#define MESSAGEHISTORY_HPP

#include <vector>
#include "Message.hpp"
#include <iostream>

class MessageHistory {
public:
    MessageHistory() = default;

    void addMessage(Message msg);
    std::vector<Message> getHistory();
    void saveToFile(std::ostream& file);
    void loadFromFile(std::istream& file);
private:
    std::vector<Message> history = {};
};

#endif // MESSAGEHISTORY_HPP