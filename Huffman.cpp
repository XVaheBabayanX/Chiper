#include "Huffman.h"
#include <queue>

Huffman::Node::Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

bool Huffman::Compare::operator()(Node* left, Node* right) {
    return left->freq > right->freq;
}

void Huffman::buildHuffmanTree(const std::string& input) {
    std::unordered_map<char, int> freq;
    for (char ch : input) {
        freq[ch]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }

    Node* root = pq.top();
    generateCodes(root, "");
    generateReverseCodes();
}

void Huffman::generateCodes(Node* root, const std::string& str) {
    if (!root) return;

    if (root->ch != '\0') {
        huffmanCode[root->ch] = str;
    }

    generateCodes(root->left, str + "0");
    generateCodes(root->right, str + "1");
}

void Huffman::generateReverseCodes() {
    for (auto& pair : huffmanCode) {
        reverseHuffmanCode[pair.second] = pair.first;
    }
}

void Huffman::Compress(const std::string& input, std::string& output) {
    buildHuffmanTree(input);
    output.clear();
    for (char ch : input) {
        output += huffmanCode[ch];
    }
}

void Huffman::Decompress(const std::string& input, std::string& output) {
    std::string currentCode;
    output.clear();
    for (char bit : input) {
        currentCode += bit;
        if (reverseHuffmanCode.find(currentCode) != reverseHuffmanCode.end()) {
            output += reverseHuffmanCode[currentCode];
            currentCode.clear();
        }
    }
}
