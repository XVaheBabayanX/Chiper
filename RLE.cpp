#include "RLE.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void RLE::Compress(const std::string& input, std::string& output) {
    Compressed.clear();
    int count;

    for (size_t i = 0; i < input.size(); i++) {
        int number = static_cast<int>(input[i]);  
        count = 1;

        while (i < (input.size() - 1) && input[i] == input[i + 1]) {
            count++;
            i++;
        }

        if (count > 1) {
            Compressed.push_back(MARKER);
            Compressed.push_back(count);
        }

        if (number == MARKER) {
            Compressed.push_back(MARKER);
            Compressed.push_back(MARKER);
        }
        else {
            Compressed.push_back(number);
        }
    }

    std::stringstream ss;
    for (size_t i = 0; i < Compressed.size(); i++) {
        ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << Compressed[i] << " ";
    }
    output = ss.str();  
}

void RLE::Decompress(const std::string& input, std::string& output) {
    std::stringstream ss(input);
    int value;
    Compressed.clear();

    while (ss >> std::hex >> value) {
        Compressed.push_back(value);
    }

    output.clear();
    for (size_t i = 0; i < Compressed.size(); i++) {
        if (Compressed[i] == MARKER) {
            int count = Compressed[++i];
            int number = Compressed[++i];
            for (int j = 0; j < count; j++) {
                output += static_cast<char>(number);  
            }
        }
        else if (Compressed[i] == MARKER && Compressed[i + 1] == MARKER) {
            output += static_cast<char>(MARKER);  
            i++;
        }
        else {
            output += static_cast<char>(Compressed[i]);  
        }
    }
}

void RLE::printHex(const std::string& data) {
    for (size_t i = 0; i < data.size(); i++) {
        std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
    }
    std::cout << std::endl;
}
