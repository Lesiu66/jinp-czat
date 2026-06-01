#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>


class Message {
public:
    Message(const std::vector<unsigned char>& msg, int sender, int receiver, int64_t time)
        : encryptedMessage(msg), senderId(sender), receiverId(receiver), timestamp(time) {}

    std::ostream& operator<<(std::ostream& os) {
        os << "Sender: " << senderId << "\nReceiver: " << receiverId << "\nTimestamp: " << getTimestampAsString << "\nMessage: " << getEncryptedAsHexString();
        return os;
    }

    std::string getEncryptedAsHexString() const;
    std::string getTimestampAsString() const;

    std::vector<unsigned char> getMessage() { return encryptedMessage; }

    std::vector<uint8_t> serialize() const;
    static Message deserialize(const std::vector<uint8_t>& buffer);

private:
    std::vector<unsigned char> encryptedMessage;
    int senderId;
    int receiverId;
    int64_t timestamp;
};

#endif // MESSAGE_HPP