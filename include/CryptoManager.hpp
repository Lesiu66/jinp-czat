#ifndef CRYPTOMANAGER_HPP
#define CRYPTOMANAGER_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

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

class XORCryptoManager : public CryptoManager {
public:
    void generateKeys() override;
    Bytes encrypt(const std::string& msg) override;
    std::string decrypt(const Bytes& msg) override;
private:
    Bytes key;
};

#endif // CRYPTOMANAGER_HPP