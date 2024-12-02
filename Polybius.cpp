#include "Polybius.h"

PolybiusCipher::PolybiusCipher()
{
    generatePolybiusSquare();
}

PolybiusCipher::PolybiusCipher(const std::string& key)
{
    setKey(key);
    generatePolybiusSquare();
}

void PolybiusCipher::setKey(const std::string& key)
{
    std::string modifiedKey = key;
    if (!isASCII(modifiedKey))
        throw std::runtime_error("Key contains non-ASCII characters");

    removeDuplicates(modifiedKey);
    Key = modifiedKey;
    generatePolybiusSquare();
}

std::string PolybiusCipher::getKey() const
{
    return Key;
}

void PolybiusCipher::removeDuplicates(std::string& text)
{
    std::unordered_set<char> seen;
    text.erase(std::remove_if(text.begin(), text.end(), [&](char c) {
        if (seen.count(c))
            return true;
        seen.insert(c);
        return false;
        }), text.end());
}

bool PolybiusCipher::isASCII(const std::string& text)
{
    return std::all_of(text.begin(), text.end(), [](unsigned char c) {
        return c >= 0 && c < ASCII;
        });
}

void PolybiusCipher::generatePolybiusSquare()
{
    std::vector<bool> used(ASCII, false);
    int row = 0, col = 0;

    if (!Key.empty())
    {
        for (char c : Key)
        {
            if (!used[static_cast<unsigned char>(c)])
            {
                PolybiusSquare[row][col++] = c;
                used[static_cast<unsigned char>(c)] = true;
                if (col == DIM)
                {
                    col = 0;
                    row++;
                }
            }
        }
    }

    for (int i = 0; i < ASCII; i++)
    {
        if (!used[i])
        {
            PolybiusSquare[row][col++] = static_cast<char>(i);
            if (col == DIM)
            {
                col = 0;
                row++;
            }
        }
    }
}

void PolybiusCipher::Encrypt(const std::string& input, std::string& output)
{
    output.clear();
    for (char c : input)
    {
        bool found = false;
        for (int i = 0; i < DIM && !found; i++)
        {
            for (int j = 0; j < DIM && !found; j++)
            {
                if (PolybiusSquare[i][j] == c)
                {
                    output += static_cast<char>(i);
                    output += static_cast<char>(j);
                    found = true;
                }
            }
        }
    }
}

void PolybiusCipher::Decrypt(const std::string& input, std::string& output)
{
    if (input.size() % 2 != 0)
        throw std::runtime_error("Invalid encrypted input length");

    output.clear();
    for (size_t i = 0; i < input.size(); i += 2)
    {
        int row = static_cast<unsigned char>(input[i]);
        int col = static_cast<unsigned char>(input[i + 1]);

        if (row >= DIM || col >= DIM)
            throw std::runtime_error("Invalid encrypted character indices");

        output += PolybiusSquare[row][col];
    }
}

void PolybiusCipher::printPolybiusSquare() const
{
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            std::cout << PolybiusSquare[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

