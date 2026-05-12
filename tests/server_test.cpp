#include <gtest/gtest.h>
#include "Server.hpp"

#include <thread>
#include <chrono>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

static int connectClient()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sock, (sockaddr*)&addr, sizeof(addr));
    return sock;
}

TEST(ServerPairMapTest, TwoClientsArePaired)
{
    Server server;

    std::thread t([&]() {
        server.start();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    int a = connectClient();
    int b = connectClient();

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    const char* msg = "hello";
    send(a, msg, 5, 0);

    char buffer[1024];
    int bytes = recv(b, buffer, sizeof(buffer), 0);

    std::string received(buffer, bytes);

    EXPECT_EQ(received, "hello");

    close(a);
    close(b);

    t.detach();
}