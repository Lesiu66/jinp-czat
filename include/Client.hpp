#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <thread>
#include <memory>
#include "User.hpp"

class Client {
private:
    int clientSocket;

public:
    std::unique_ptr<User> user;
    Client(std::unique_ptr<User> u);
    ~Client();

    void connectToServer();

    void sendMessage(const std::string& rawMessage);

    void startReceiving();
};

#endif
