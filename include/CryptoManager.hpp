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

    virtual Bytes generateKeys(size_t length) = 0;

    virtual Bytes encrypt(const std::string& msg) = 0;

    virtual std::string decrypt(const Bytes& msg) = 0;

    void setKey(const Bytes& k) {key = k;}
    Bytes getKey() {return key;}

protected:
    Bytes stringToBytes(const std::string& text) const {
        return Bytes(text.begin(), text.end());
    }
    
    std::string bytesToString(const Bytes& bytes) const {
        return std::string(bytes.begin(), bytes.end());
    }
    
    Bytes key;
};

class XORCryptoManager : public CryptoManager {
public:
    Bytes generateKeys(size_t length) override;
    Bytes encrypt(const std::string& msg) override;
    std::string decrypt(const Bytes& msg) override;
};

class AESCryptoManager : public CryptoManager {
public:
    Bytes generateKeys(size_t length) override;
    Bytes encrypt(const std::string& msg) override;
    std::string decrypt(const Bytes& msg) override;
};

#endif // CRYPTOMANAGER_HPP