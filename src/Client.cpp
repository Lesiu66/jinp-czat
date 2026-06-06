#include "Client.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client(std::unique_ptr<User> u) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    user = std::move(u);
}

Client::~Client() {
    close(clientSocket);
}

void Client::connectToServer() {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket,
                (sockaddr*)&serverAddr,
                sizeof(serverAddr)) < 0) {

        std::cerr << "Connection failed\n";
        return;
    }

    std::cout << "Connected to server\n";
}

void Client::sendMessage(const std::string& rawMessage) {
    std::vector<uint8_t> encryptedMessage = user->encryptData(rawMessage);

    auto now = std::chrono::system_clock::now();
    int64_t currentTimestamp =
        std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()).count();

    Message message(TEXT_MESSAGE,
                    encryptedMessage,
                    user->getId(),
                    0,
                    currentTimestamp);

    std::vector<uint8_t> serializedPacket = message.serialize();

    send(clientSocket,
         serializedPacket.data(),
         serializedPacket.size(),
         0);
}

void Client::startReceiving() {

    std::thread([this]() {

        while (true) {

            std::vector<uint8_t> buffer(1024);

            int bytes = recv(clientSocket,
                             buffer.data(),
                             buffer.size(),
                             0);

            if (bytes <= 0)
                break;

            buffer.resize(bytes);

            Message receivedMsg = Message::deserialize(buffer);

            std::string clearText =
                user->decryptData(receivedMsg.getMessage());

            std::cout << "\n[" << receivedMsg.getTimestampAsString() << "] "
                      << "User " << receivedMsg.getSenderId() << ": "
                      << clearText << std::endl;
        }

    }).detach();
}
