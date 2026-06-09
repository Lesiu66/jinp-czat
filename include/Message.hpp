#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>

enum MessageType : uint8_t {
    TEXT_MESSAGE,
    KEY,
    PAIR_READY,
    INIT
};

class Message {
public:
    Message(MessageType type, const std::vector<unsigned char>& msg, int sender, int receiver, int64_t time)
        : type(type), encryptedMessage(msg), senderId(sender), receiverId(receiver), timestamp(time) {}

    friend std::ostream& operator<<(std::ostream& os, const Message& msg) {
        os << msg.senderId << " "
       << msg.receiverId << " "
       << msg.timestamp << " "
       << msg.getEncryptedAsHexString();

        return os;
    }

    std::string getEncryptedAsHexString() const;
    std::string getTimestampAsString() const;

    std::vector<unsigned char> getMessage() { return encryptedMessage; }
    MessageType getType() { return type; }

    int getSenderId() const {
        return senderId;
    }

    int getReceiverId() const {
        return receiverId;
    }

    int64_t getTimestamp() const {
        return timestamp;
    }

    std::vector<uint8_t> serialize() const;
    static Message deserialize(const std::vector<uint8_t>& buffer);

private:
    MessageType type;
    std::vector<unsigned char> encryptedMessage;
    int senderId;
    int receiverId;
    int64_t timestamp;
};

#endif // MESSAGE_HPP