#pragma once

#include <string>
#include <unordered_map>

class Huffman
{
private:
    struct Node {
        char ch;
        int freq;
        Node* left;
        Node* right;

        Node(char c, int f);
    };

    struct Compare {
        bool operator()(Node* left, Node* right);
    };

    std::unordered_map<char, std::string> huffmanCode;
    std::unordered_map<std::string, char> reverseHuffmanCode;

    void buildHuffmanTree(const std::string& input);
    void generateCodes(Node* root, const std::string& str);
    void generateReverseCodes();

public:
    void Compress(const std::string& input, std::string& output);
    void Decompress(const std::string& input, std::string& output);
};
