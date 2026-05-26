#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <thread>
#include "User.hpp"

class Client {
private:
    int clientSocket;
    User user;

public:
    Client(User u);
    ~Client();

    void connectToServer();

    void sendMessage(const std::string& rawMessage);

    void startReceiving();
};

#endif
