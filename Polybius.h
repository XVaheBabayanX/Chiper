#pragma once

#include "Crypto.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>

class PolybiusCipher : public Crypto
{
public:
    PolybiusCipher();
    PolybiusCipher(const std::string& key);

    void Encrypt(const std::string& input, std::string& output) override;
    void Decrypt(const std::string& input, std::string& output) override;

    void setKey(const std::string& key);
    std::string getKey() const;

    void printPolybiusSquare() const;

private:
    static const int ASCII = 256;
    static const int DIM = 16; 

    std::string Key;
    char PolybiusSquare[DIM][DIM];

    void generatePolybiusSquare();
    void removeDuplicates(std::string& text);
    bool isASCII(const std::string& text);
};