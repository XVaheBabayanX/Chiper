#pragma once

#include "Crypto.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

class TranspositionCipher : public Crypto
{
private:
    size_t Key;
    size_t Rows, Columns;
    char Space = ' ';
    void setTableSize(const std::string& input);
    size_t KeyRandomSize;
    void setKeyRandomSize(size_t Size);
    static const int ASCII = 256;
    static const size_t MIN_KEY_SIZE = 1;
    std::vector<std::string> Table;
    void DeleteTable();
    void CreateEncryptTable(const std::string& input);
    void CreateDecryptTable(const std::string& input);
    std::string CreateEncryptString(std::string& output);
    std::string CreateDecryptString(std::string& output);

public:
    TranspositionCipher();
    TranspositionCipher(size_t key);
    void setKey(size_t key);
    size_t GenerateRandomKey(size_t Size);
    void Encrypt(const std::string& input, std::string& output) override;
    void Decrypt(const std::string& input, std::string& output) override;
    void PrintTable();
};