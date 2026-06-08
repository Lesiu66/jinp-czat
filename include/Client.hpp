#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <thread>
#include <memory>
#include "User.hpp"
#include "Message.hpp"

class Client {
private:
    int clientSocket;
    bool keyReady = false;

public:
    std::unique_ptr<User> user;
    Client(std::unique_ptr<User> u);
    ~Client();

    void connectToServer();

    void sendMessage(const std::string& rawMessage);

    void generateSymmetricKey();

    void startReceiving();
};

#endif //CLIENT_HPP
