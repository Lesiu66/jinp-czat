#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class User;
class CryptoManager;

class Client {
private:
    int socket;
    User* user;
    CryptoManager* crypto;

public:
    Client(int socket, User* user);

    void connectToServer();
    void sendMessage(const std::string& message);
    void receiveMessage(const std::string& message);

    std::string encryptMessage(const std::string& message);
    std::string decryptMessage(const std::string& message);

};

#endif // CLIENT_HPP
