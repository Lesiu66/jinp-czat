#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include "Client.hpp"

class Server {
public:
    Server(std::vector<Client*> list): clientsList(list) {};

    void start();
    void acceptClient(Client client);
    void forwardMessage();
private:
    std::vector<Client*> clientsList;
};

#endif // SERVER_HPP