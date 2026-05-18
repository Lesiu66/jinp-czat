#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <thread>

class Client {
private:
    int clientSocket;

public:
    Client();
    ~Client();

    void connectToServer();

    void sendMessage(const std::string& message);

    void startReceiving();
};

#endif
