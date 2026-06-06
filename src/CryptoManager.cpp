#include "CryptoManager.hpp"
#include <stdexcept>

Bytes XORCryptoManager::generateKeys(size_t length) {
    Bytes newKey;
    newKey.resize(length);

    if (RAND_bytes(newKey.data(), static_cast<int>(newKey.size())) != 1) {
        throw std::runtime_error("OpenSSL ERROR: Could not generate key!");
    }

    return newKey;
    //newKey.assign(length, 0x22);
}

Bytes XORCryptoManager::encrypt(const std::string& msg) {
    if (key.empty()) {
        throw std::runtime_error("ERROR: Generate key first!");
    }

    Bytes data = stringToBytes(msg);
    Bytes encryptedMsg(data.size());

    for (int i=0;i<data.size();i++) {
        encryptedMsg[i] = data[i] ^ key[i % key.size()];
    }

    return encryptedMsg;
}

std::string XORCryptoManager::decrypt(const Bytes& msg) {
    if (key.empty()) {
        throw std::runtime_error("ERROR: Generate key first!");
    }

    Bytes decryptedData(msg.size());

    for (int i=0;i<msg.size();i++) {
        decryptedData[i] = msg[i] ^ key[i % key.size()];
    }

    return bytesToString(decryptedData);
}
