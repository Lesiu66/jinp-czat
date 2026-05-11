#include "Client.hpp"
#include <iostream>
#include <string>

int main() {

    Client client;

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
