#include "Server.hpp"

void Server::acceptClient(Client client) {
    clientsList.push_back(&client);
}