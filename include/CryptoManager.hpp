#ifndef CRYPTOMANAGER_HPP
#define CRYPTOMANAGER_HPP

#include <vector>
#include <string>
#include <cstdint>

using Bytes = std::vector<uint8_t>;

class CryptoManager {
public:
    virtual ~CryptoManager() = default; 

    virtual void generateKeys() = 0;

    virtual Bytes encrypt(const std::string& msg) = 0;

    virtual std::string decrypt(const Bytes& msg) = 0;
protected:
    Bytes stringToBytes(const std::string& text) const {
        return Bytes(text.begin(), text.end());
    }
    
    std::string bytesToString(const Bytes& bytes) const {
        return std::string(bytes.begin(), bytes.end());
    }
};

#endif // CRYPTOMANAGER_HPP