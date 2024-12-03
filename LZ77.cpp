#include "LZ77.h"
#include <sstream>
#include <iostream>

LZ77::LZ77(int window, int lookahead) : windowSize(window), lookaheadBufferSize(lookahead) {}

void LZ77::Compress(const std::string& input, std::string& output) {
    std::vector<char> inputVec(input.begin(), input.end());
    std::vector<Token> tokens = CompressToTokens(inputVec);

    std::ostringstream oss;
    for (const auto& token : tokens) {
        oss << token.offset << ' ' << token.length << ' ' << (int)token.nextChar << ' ';
    }

    output = oss.str();
    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }
}

void LZ77::Decompress(const std::string& input, std::string& output) {
    std::vector<Token> tokens;
    std::istringstream iss(input);
    int offset, length;
    int nextCharInt;
    char nextChar;

    while (iss >> offset >> length >> nextCharInt) {
        nextChar = static_cast<char>(nextCharInt);
        tokens.push_back({ offset, length, nextChar });
    }

    std::vector<char> decompressedData = DecompressFromTokens(tokens);
    output.assign(decompressedData.begin(), decompressedData.end());
}

std::vector<LZ77::Token> LZ77::CompressToTokens(const std::vector<char>& input) {
    std::vector<Token> tokens;
    int pos = 0;

    while (pos < input.size()) {
        int bestLength = 0;
        int bestOffset = 0;
        char nextChar = input[pos];

        int searchStart = std::max(0, pos - windowSize);
        for (int i = searchStart; i < pos; ++i) {
            int length = 0;
            while (length < lookaheadBufferSize && pos + length < input.size() &&
                input[i + length] == input[pos + length]) {
                ++length;
            }
            if (length > bestLength) {
                bestLength = length;
                bestOffset = pos - i;
                if (pos + length < input.size()) {
                    nextChar = input[pos + length];
                }
                else {
                    nextChar = '\0';
                }
            }
        }

        tokens.push_back({ bestOffset, bestLength, nextChar });
        pos += bestLength + 1;
    }

    return tokens;
}

std::vector<char> LZ77::DecompressFromTokens(const std::vector<Token>& tokens) {
    std::vector<char> output;
    for (const auto& token : tokens) {
        if (token.offset == 0 && token.length == 0) {
            output.push_back(token.nextChar);
        }
        else {
            size_t start = output.size() - token.offset;
            for (int i = 0; i < token.length; ++i) {
                output.push_back(output[start + i]);
            }
            output.push_back(token.nextChar);
        }
    }
    return output;
}
