#pragma once

#include <string>
#include <unordered_map>
#include <vector>

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

    Node* root; 
    std::unordered_map<char, std::string> huffmanCode;
    std::unordered_map<std::string, char> reverseHuffmanCode;

    void buildHuffmanTree(const std::string& input);
    void buildHuffmanTreeFromNodes(const std::vector<std::pair<char, int>>& nodes);
    void generateCodes(Node* root, const std::string& str);
    void generateReverseCodes();
    void printTreeHelper(Node* node, int level) const;
    void deleteTree(Node* node);  

public:
    Huffman() : root(nullptr) {}  
    ~Huffman();  

    void Compress(const std::string& input, std::string& output);
    void Decompress(const std::string& input, std::string& output);
    void setTreeFromInput(const std::string& input);
    void printTree() const;
};