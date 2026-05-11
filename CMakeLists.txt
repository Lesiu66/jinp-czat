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

# SERVER

set(SERVER_SOURCES
    src/server_main.cpp
    src/Server.cpp
)

add_executable(server ${SERVER_SOURCES})

target_include_directories(server PUBLIC include)

target_link_libraries(server
    PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

# CLIENT

set(CLIENT_SOURCES
    src/client_main.cpp
    src/Client.cpp
)

add_executable(client ${CLIENT_SOURCES})

target_include_directories(client PUBLIC include)

target_link_libraries(client
    PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

# TESTS

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(test_chat
    tests/server_test.cpp
    tests/client_test.cpp
    src/Server.cpp
    src/Client.cpp
)

target_include_directories(test_chat PUBLIC include)

target_link_libraries(test_chat
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

gtest_discover_tests(test_chat)
