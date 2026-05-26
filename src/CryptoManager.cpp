#include "CryptoManager.hpp"
#include <stdexcept>

void XORCryptoManager::generateKeys() {
    key.resize(16);

    // if (RAND_bytes(key.data(), static_cast<int>(key.size())) != 1) {
    //     throw std::runtime_error("OpenSSL ERROR: Could not generate key!");
    // }
    key.assign(16, 0x22);
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
