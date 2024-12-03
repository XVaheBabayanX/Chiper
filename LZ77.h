#pragma once

#include <vector>
#include <string>

class LZ77 {
private:
    int windowSize;
    int lookaheadBufferSize;

public:
    LZ77(int window = 4096, int lookahead = 18);

    void Compress(const std::string& input, std::string& output);
    void Decompress(const std::string& input, std::string& output);

    struct Token {
        int offset;
        int length;
        char nextChar;
    };

private:
    std::vector<Token> CompressToTokens(const std::vector<char>& input);
    std::vector<char> DecompressFromTokens(const std::vector<Token>& tokens);
};