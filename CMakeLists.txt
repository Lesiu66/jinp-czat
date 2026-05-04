cmake_minimum_required(VERSION 3.10)

project(
    CypherChat
    VERSION 1.0.0
    DESCRIPTION "Secure chat application using AES and RSA encryption"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

set(SOURCES
    src/main.cpp
    src/Server.cpp
    src/Client.cpp
    src/User.cpp
    src/Message.cpp
    src/MessageHistory.cpp
    src/CryptoManager.cpp
)

add_executable(CypherChat ${SOURCES})

target_include_directories(CypherChat PUBLIC include)

target_link_libraries(CypherChat
    PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

enable_testing()
include(CTest)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(test_chat
    tests/test.main.cpp
)

target_link_libraries(test_chat
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

gtest_discover_tests(test_chat)
