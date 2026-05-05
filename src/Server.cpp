#include "Server.hpp"

void Server::acceptClient(Client client) {
    clientList.pushback(client);
}