#pragma once

#include <vector>
#include <string>

class RLE
{
private:
    const int MARKER = 255;  
    std::vector<int> Compressed;

public:
    void Compress(const std::string& input, std::string& output);
    void Decompress(const std::string& input, std::string& output);

    void printHex(const std::string& data);
};
