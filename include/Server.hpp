#ifndef SERVER_HPP
#define SERVER_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <map>

class Server {
public:
    Server();
    ~Server();

    void start();

private:
    int serverSocket;
    std::vector<int> clients;
    std::unordered_map<int, int> pairMap;
    std::map<int, std::string> clientNames;

    void acceptClients();
    void handleClient(int clientSocket);
    void forwardMessage(int senderSocket, const char* buffer, int size);
    void tryPairClients();
};

#endif //SERVER_HPP
