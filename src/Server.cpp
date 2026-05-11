#include "Server.hpp"

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>

Server::Server() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
}

Server::~Server() {
    close(serverSocket);
}

void Server::start() {

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(serverSocket,
             (sockaddr*)&serverAddr,
             sizeof(serverAddr)) < 0) {

        std::cerr << "Bind failed\n";
        return;
    }

    listen(serverSocket, 10);

    std::cout << "Server started\n";

    acceptClients();
}

void Server::acceptClients() {

    while (true) {

        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket < 0) continue;

        std::cout << "Client connected: " << clientSocket << "\n";

        clients.push_back(clientSocket);

        tryPairClients();

        std::thread(&Server::handleClient,
                    this,
                    clientSocket).detach();
    }
}

void Server::tryPairClients() {

    if (clients.size() < 2) return;

    int a = clients[clients.size() - 2];
    int b = clients[clients.size() - 1];

    pairMap[a] = b;
    pairMap[b] = a;

    std::cout << "Paired: " << a << " <-> " << b << "\n";
}

void Server::handleClient(int clientSocket) {

    char buffer[1024];

    while (true) {

        int bytes = recv(clientSocket,
                         buffer,
                         sizeof(buffer),
                         0);

        if (bytes <= 0) {

            std::cout << "Client disconnected\n";

            clients.erase(std::remove(clients.begin(),
                                       clients.end(),
                                       clientSocket),
                          clients.end());

            pairMap.erase(clientSocket);

            close(clientSocket);
            return;
        }

        std::string msg(buffer, bytes);

        forwardMessage(clientSocket, msg);
    }
}

void Server::forwardMessage(int senderSocket,
                            const std::string& msg)
{
    if (pairMap.find(senderSocket) == pairMap.end())
        return;

    int target = pairMap[senderSocket];

    send(target, msg.c_str(), msg.size(), 0);
}

int Server::findPartner(int clientId, const std::vector<int>& currentClients) {
    if (currentClients.size() < 2) return -1;

    for (size_t i = 0; i < currentClients.size(); ++i) {
        if (currentClients[i] == clientId) {
            if (i % 2 == 0 && i + 1 < currentClients.size()) return currentClients[i+1];
            if (i % 2 != 0) return currentClients[i-1];
        }
    }
    return -1;
}