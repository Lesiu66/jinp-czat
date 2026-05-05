#ifndef MESSAGEHISTORY_HPP
#define MESSAGEHISTORY_HPP

#include <vector>
#include "Message.hpp"
#include <iostream>

class MessageHistory {
public:
    void addMessage(Message msg);
    std::vector<Message> getHistory();
    void saveToFile(&std::ostream);
    void loadFromFile(&std::istream);
private:
    std::vector<Message>;
};

#endif // MESSAGEHISTORY_HPP