#pragma once
#pragma once

#include "Crypto.h"
#include <string>

class SimpleSubstitutionCipher : public Crypto
{
private:
    std::string Key;
    static const int ASCII = 256;

public:
    SimpleSubstitutionCipher();

    void Encrypt(const std::string& OriginalText, std::string& EncryptedText) override;
    void Decrypt(const std::string& EncryptedText, std::string& DecryptedText) override;

private:
    void GenerateRandomKey();
};
