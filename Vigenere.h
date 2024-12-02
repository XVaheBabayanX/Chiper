#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include "Crypto.h"

class VigenereCipher : public Crypto
{
public:
    VigenereCipher();
    VigenereCipher(const std::string& key);

    void Encrypt(const std::string& input, std::string& output) override;
    void Decrypt(const std::string& input, std::string& output) override;

    void setKey(const std::string& key);

    std::string getKey() const;
    std::string getEncrypted() const;
    std::string getDecrypted() const;

    void GenerateVigenereSquare();
    void printVigenereSquare();

private:
    static const int ASCII = 256;

    std::string Key, Encrypted, Decrypted;
    char VigenereSquare[ASCII][ASCII];

    void removeDuplicates(std::string& text);
    bool isASCII(const std::string& text);
};
