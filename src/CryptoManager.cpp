#include "CryptoManager.hpp"
#include <stdexcept>

Bytes CryptoManager::generateKeys(size_t length = 32) {
    Bytes newKey;
    newKey.resize(length);

    if (RAND_bytes(newKey.data(), static_cast<int>(newKey.size())) != 1) {
        throw std::runtime_error("OpenSSL ERROR: Could not generate key!");
    }

    return newKey;
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

Bytes AESCryptoManager::encrypt(const std::string& msg) {
    Bytes iv(16);
    RAND_bytes(iv.data(), 16);

    Bytes data = stringToBytes(msg);
    Bytes encryptedMsg(data.size() + 16);

    int outLen1 = 0, outLen2 = 0;

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key.data(), iv.data());
    EVP_EncryptUpdate(ctx, encryptedMsg.data(), &outLen1, data.data(), data.size());
    EVP_EncryptFinal_ex(ctx, encryptedMsg.data() + outLen1, &outLen2);

    encryptedMsg.resize(outLen1 + outLen2);
    EVP_CIPHER_CTX_free(ctx);

    return encryptedMsg;
}

std::string AESCryptoManager::decrypt(const Bytes& msg) {
    if (msg.size() < 16) {
        throw std::runtime_error("Message with iv too short!");
    }

    Bytes iv(msg.begin(), msg.begin() + 16);
    
    Bytes encryptedMsg(msg.begin() + 16, msg.end());

    Bytes plaintext(encryptedMsg.size());
    int outLen1 = 0, outLen2 = 0;

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key.data(), iv.data());
    EVP_DecryptUpdate(ctx, plaintext.data(), &outLen1, encryptedMsg.data(), encryptedMsg.size());
    EVP_DecryptFinal_ex(ctx, plaintext.data() + outLen1, &outLen2);

    plaintext.resize(outLen1 + outLen2);
    return std::string(plaintext.begin(), plaintext.end());
}