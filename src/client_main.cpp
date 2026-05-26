#include "Client.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

int main() {
    std::string username;
    std::cout << "Enter username:\n";
    std::cin >> username;
    Client client(std::make_unique<User>(User(rand(), username, std::make_unique<XORCryptoManager>(XORCryptoManager()))));
    client.user->generateUserKey();

    client.connectToServer();
    client.startReceiving();

    std::string msg;

    std::cout << "Enter message:\n";

    while (true) {

        std::getline(std::cin, msg);

        if (msg == "exit")
            break;

        client.sendMessage(msg);
    }

    return 0;
}
