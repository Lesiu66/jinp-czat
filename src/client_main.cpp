#include "Client.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <limits>
#include <fstream>
#include <csignal>

volatile std::sig_atomic_t keepRunning = true;

void signalHandler(int signum) {
    keepRunning = false; 
}

int main() {
    std::signal(SIGINT, signalHandler);

    srand(time(nullptr));
    
    std::string username, password, filePath;

    AESCryptoManager crypto;
    auto msgHistory = std::make_unique<MessageHistory>(&crypto);

    std::cout << "Enter username:\n";
    std::cin >> username;
    std::cout << "Enter file path:\n";
    std::cin >> filePath;
    std::cout << "Enter password:\n";
    std::cin >> password;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Client client(
        std::make_unique<User>(rand(), username, std::make_unique<AESCryptoManager>(), std::move(msgHistory))
    );

    std::ifstream infile(filePath);
    if (infile.is_open()) {
        client.user->history->loadFromFile(infile);
        infile.close();
    } else {
        std::cout << "History file not found. A new one will be created upon exit.\n";
    }

    client.user->history->displayHistory();

    client.connectToServer();
    client.startReceiving();

    std::string msg;

    while (keepRunning) {
        std::getline(std::cin, msg);

        if (msg == "exit" || !keepRunning)
            break;

        client.sendMessage(msg);
    }

    std::ofstream outfile(filePath, std::ios::trunc);
    if (outfile.is_open()) {
        client.user->history->saveToFile(outfile);
        outfile.close();
        std::cout << "History saved successfully.\n";
    } else {
        std::cerr << "Error: Could not save history to file!\n";
    }

    return 0;
}