#include "Client.hpp"
#include "User.hpp"
#include "CryptoManager.hpp"

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client(int socket, User* user)
    : socket(socket), user(user), crypto(nullptr) {}

void Client::connectToServer() {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed\n";
        return;
    }

    std::cout << user->getUsername() << " connected to server\n";
}

void Client::sendMessage(const std::string& message) {
    std::string encrypted = encryptMessage(message);

    send(socket, encrypted.c_str(), encrypted.size(), 0);

    std::cout << "Sent: " << encrypted << std::endl;
}

void Client::receiveMessage() {
    char buffer[1024] = {0};

    int bytes = recv(socket, buffer, sizeof(buffer), 0);

    if (bytes > 0) {
        std::string message(buffer, bytes);
        std::cout << "Received: " << decryptMessage(message) << std::endl;
    }
}

std::string Client::encryptMessage(const std::string& message) {
    return crypto ? crypto->encryptAES(message) : message;
}

std::string Client::decryptMessage(const std::string& message) {
    return crypto ? crypto->decryptAES(message) : message;
}
