#include "MessageHistory.hpp"

void MessageHistory::addMessage(const std::string& msg, int senderId, int receiverId, int64_t timestamp) {
    Bytes encryptedMsg = manager->encrypt(msg);
    Message message(TEXT_MESSAGE, encryptedMsg, senderId, receiverId, timestamp);
    history.push_back(message);
}

std::vector<Message> MessageHistory::getHistory() {
    return history;
}

void MessageHistory::saveToFile(std::ostream& file) {
    for (const auto& msg : history) {
        file<<msg<<std::endl;
    }
}

Bytes hexToBytes(const std::string& hex) {
    Bytes bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

void MessageHistory::loadFromFile(std::istream& file) {
    std::string line;
    history.clear();

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        
        int sender;
        int receiver;
        std::string date;
        int64_t timestamp;
        std::string hexData;

        if (ss >> sender >> receiver >> timestamp >> hexData) {
            Bytes decodedMessage = hexToBytes(hexData);

            Message msg(TEXT_MESSAGE ,decodedMessage, sender, receiver, timestamp);
            
            history.push_back(msg);
        }
    }
}

void MessageHistory::displayHistory() {
    if (history.size() < 1) return;
    std::cout << "--- Message history ---" << std::endl;
    for (auto& msg : history) {
        std::string clearText = manager->decrypt(msg.getMessage());

        size_t separatorPos = clearText.find('|');

        if (separatorPos != std::string::npos) {
            std::string senderName = clearText.substr(0, separatorPos);
            std::string actualMessage = clearText.substr(separatorPos + 1);
            std::cout << "\n[" << msg.getTimestampAsString() << "] "
                      << senderName << ": " << actualMessage << std::endl;
        } 
        else {
            std::cout << "\n[" << msg.getTimestampAsString() << "] "
                      << "User " << msg.getSenderId() << ": "
                      << clearText << std::endl;
        }
    }
    std::cout << "--- End of History ---" << std::endl;
}