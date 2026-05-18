#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <string>

class Message {
public:
    
private:
    std::vector<unsigned char> encryptedMessage;
    int senderId;
    int receiverId;
    std::string timestamp;
};

#endif // MESSAGE_HPP