#include "MessageHistory.hpp"

void MessageHistory::addMessage(Message msg) {
    history.push_back(msg);
}

std::vector<Message> MessageHistory::getHistory() {
    return history;
}

void MessageHistory::saveToFile(std::ostream& file) {
    for (const auto& msg : history) {
        file<<&msg<<std::endl;
    }
}

std::vector<unsigned char> hexToBytes(const std::string& hex) {
    std::vector<unsigned char> bytes;
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
        std::string time;
        std::string hexData;

        if (ss >> sender >> receiver >> date >> time >> hexData) {
            std::string fullTimestamp = date + " " + time;
            std::vector<unsigned char> decodedMessage = hexToBytes(hexData);

            Message msg(decodedMessage, sender, receiver, fullTimestamp);
            
            history.push_back(msg);
        }
    }
}