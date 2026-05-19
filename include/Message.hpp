#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

class Message {
public:
    Message(const std::vector<unsigned char>& msg, int sender, int receiver, const std::string& time)
        : encryptedMessage(msg), senderId(sender), receiverId(receiver), timestamp(time) {}

    std::ostream& operator<<(std::ostream& os) {
        os << "Sender: " << senderId << "\nReceiver: " << receiverId << "\nTimestamp: " << timestamp << "\nMessage: " << getEncryptedAsHexString();
        return os;
    }

    std::string getEncryptedAsHexString() const {
        std::stringstream ss;
        
        for (unsigned char bajt : encryptedMessage) {
            ss << std::hex
            << std::setw(2)
            << std::setfill('0')
            << (int)bajt;
        }
        
        return ss.str();
    }

private:
    std::vector<unsigned char> encryptedMessage;
    int senderId;
    int receiverId;
    std::string timestamp;
};

#endif // MESSAGE_HPP