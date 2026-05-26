#include "Client.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

int main() {
    std::string username;
    std::cout << "Enter username:\n";
    std::cin >> username;
    Client client(User(rand(), username, std::make_unique<CryptoManager>(XORCryptoManager())));

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
