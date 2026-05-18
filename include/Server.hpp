#ifndef SERVER_HPP
#define SERVER_HPP

#include <unordered_map>
#include <vector>
#include <string>

class Server {
public:
    Server();
    ~Server();

    void start();

private:
    int serverSocket;

    std::vector<int> clients;

    std::unordered_map<int, int> pairMap;

    void acceptClients();
    void handleClient(int clientSocket);
    void forwardMessage(int senderSocket, const std::string& msg);
    void tryPairClients();
};

#endif
