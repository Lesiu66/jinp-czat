#include <gtest/gtest.h>
#include "Server.hpp"

TEST(ServerLogicTest, OneClient) {
    Server s;
    std::vector<int> clients = {101};
    
    int result = s.findPartner(101, clients);
    
    EXPECT_EQ(result, -1);
}

TEST(ServerLogicTest, ValidPair) {
    Server s;
    std::vector<int> clients = {101, 102};
    
    int partnerOfFirst = s.findPartner(101, clients);
    int partnerOfSecond = s.findPartner(102, clients);
    
    EXPECT_EQ(partnerOfFirst, 102);
    EXPECT_EQ(partnerOfSecond, 101);
}

TEST(ServerLogicTest, OddClients) {
    Server s;
    std::vector<int> ids = {1, 2, 3};
    EXPECT_EQ(s.findPartner(1, ids), 2);
    EXPECT_EQ(s.findPartner(3, ids), -1);
}

TEST(ServerLogicTest, Empty) {
    Server s;
    EXPECT_EQ(s.findPartner(99, {}), -1);
}
