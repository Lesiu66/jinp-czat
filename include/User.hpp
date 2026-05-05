#ifndef USER_HPP
#define USER_HPP

class User {
public:
    User(int ID, std::string Username): id(ID), username(Username) {generateKeys();}

    void generateKeys();
private:
    int id;
    std::string username;
    std::string publicKey;
    std::string privateKey;
};

#endif // USER_HPP