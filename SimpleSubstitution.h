#pragma once

#include "Crypto.h"
#include <string>
#include <unordered_set>
#include <unordered_map>

class SimpleSubstitutionCipher : public Crypto
{
private:
    std::string Key;
    std::string Alphabet;
    std::unordered_map<char, char> reverseAlphabet;
    static const int ASCII = 256;

public:
    SimpleSubstitutionCipher();
    SimpleSubstitutionCipher(const std::string& key);

    void setKey(const std::string& key);
    std::string getKey() const;
    void printAlphabet() const;

    void Encrypt(const std::string& OriginalText, std::string& EncryptedText) override;
    void Decrypt(const std::string& EncryptedText, std::string& DecryptedText) override;

private:
    void GenerateRandomAlphabet();
    void GenerateAlphabet();
    void GenerateReverseAlphabet();
    void removeDuplicates(std::string& text);
};
