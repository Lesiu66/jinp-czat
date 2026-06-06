#include "Client.hpp"
#include "MessageHistory.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <limits>
#include <fstream>

int main() {
    std::string username;

    std::cout << "Enter username:\n";
    std::cin >> username;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Client client(
        std::make_unique<User>(
            User(rand(),
                 username,
                 std::make_unique<XORCryptoManager>(XORCryptoManager()))
        )
    );

    client.user->generateUserKey(32);

    client.connectToServer();
    client.startReceiving();

    std::string msg;

    while (true) {
        std::getline(std::cin, msg);

        if (msg == "exit")
            break;

        client.sendMessage(msg);
    }

    return 0;
}