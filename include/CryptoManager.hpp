#ifndef CRYPTOMANAGER_HPP
#define CRYPTOMANAGER_HPP

#include <vector>

class CryptoManager {
public:
    std::vector<std::string> generateRSAKeys();
    std::vector<unsigned char> encryptRSA(std::string msg);
    std::string decryptRSA(std::vector<unsigned char> msg);
    std::vector<unsigned char> encryptAES(std::string msg);
    std::string decryptAES(std::vector<unsigned char> msg);
private:

}

#endif // CRYPTOMANAGER_HPP