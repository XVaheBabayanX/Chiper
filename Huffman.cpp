#include "Huffman.h"
#include <queue>
#include <sstream>
#include <iostream>

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

    root = pq.top();
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

void Huffman::setTreeFromInput(const std::string& input) {
    std::vector<std::pair<char, int>> nodes;
    std::istringstream iss(input);
    char ch;
    int freq;
    char delimiter;

    while (iss >> ch >> freq) {
        nodes.push_back({ ch, freq });
        if (iss.peek() == ',') {
            iss >> delimiter;  
        }
    }

    buildHuffmanTreeFromNodes(nodes);
}


void Huffman::buildHuffmanTreeFromNodes(const std::vector<std::pair<char, int>>& nodes) {
    auto cmp = [](Node* left, Node* right) { return left->freq > right->freq; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

    for (const auto& pair : nodes) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;

        pq.push(sum);
    }

    root = pq.top();
    generateCodes(root, "");
    generateReverseCodes();
}

Huffman::~Huffman() {
    deleteTree(root);  
}

void Huffman::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void Huffman::printTree() const {
    printTreeHelper(root, 0);
}

void Huffman::printTreeHelper(Node* node, int level) const {
    if (node == nullptr) return;

    if (node->right) {
        printTreeHelper(node->right, level + 1);
    }

    for (int i = 0; i < level; ++i) {
        std::cout << "   ";  
    }
    if (node->ch != '\0') {
        std::cout << node->ch << ":" << node->freq << std::endl;
    }
    else {
        std::cout << "Internal Node:" << node->freq << std::endl;
    }

    if (node->left) {
        printTreeHelper(node->left, level + 1);
    }
}