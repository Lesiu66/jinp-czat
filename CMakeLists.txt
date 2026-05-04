cmake_minimum_required(VERSION 3.10)

project(
    CypherChat
    VERSION 1.0.0
    DESCRIPTION "Secure chat application that uses AES and RSA encryption to send messages between users"
    LANGUAGES CXX
)

message("Project_Name: ${PROJECT_NAME}")
message("Project_Dir: ${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenSSL REQUIRED)

set(SOURCES
    src/main.cpp
    src/Server.cpp 
    src/Client.cpp
    src/User.cpp
    src/Message.cpp
    src/MessageHistory.cpp
    src/CryptoManager.cpp
)

add_executable(main ${SOURCES})

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
include(GTest)

add_executable(test_chat
    tests/test.main.cpp)

target_link_libraries(test_chat
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

include(GoogleTest)
gtest_discover_tests(test_chat)
