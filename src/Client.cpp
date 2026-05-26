#include "Client.hpp"

#include <iostream>
#include <string>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client(User u) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    user = u;
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
    std::vector<uint8_t> msg = user.encryptData(rawMessage);
    send(clientSocket,
         msg,
         msg.size(),
         0);
}

void Client::startReceiving() {

    std::thread([this]() {

        while (true) {

            char buffer[1024] = {0};

            int bytes = recv(clientSocket,
                             buffer,
                             sizeof(buffer),
                             0);

            if (bytes <= 0)
                break;

            std::string msg = user.decryptData(buffer);

            std::cout << "\nReceived: "
                      << msg
                      << std::endl;
        }

    }).detach();
}
