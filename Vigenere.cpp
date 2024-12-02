#include "Vigenere.h"
#include <stdexcept>
#include <algorithm>

VigenereCipher::VigenereCipher()
{
    GenerateVigenereSquare();
}

VigenereCipher::VigenereCipher(const std::string& key)
{
    setKey(key);
    GenerateVigenereSquare();
}

void VigenereCipher::setKey(const std::string& key)
{
    std::string modifiedKey = key;
    try
    {
        if (isASCII(modifiedKey))
        {
            removeDuplicates(modifiedKey);
            Key = modifiedKey;
        }
        else throw std::runtime_error("None ASCII symbol(s) in Key");
    }
    catch (const std::exception& e)
    {
        std::cerr << "setKey() failed : " << e.what() << std::endl;
    }
}

std::string VigenereCipher::getKey() const
{
    return Key;
}

std::string VigenereCipher::getEncrypted() const
{
    return Encrypted;
}

std::string VigenereCipher::getDecrypted() const
{
    return Decrypted;
}

void VigenereCipher::removeDuplicates(std::string& text)
{
    std::string temp;
    for (char c : text)
    {
        if (temp.find(c) == std::string::npos)
            temp += c;
    }
    text = temp;
}

void VigenereCipher::Encrypt(const std::string& input, std::string& output)
{
    output.clear();
    size_t keyIndex = 0;
    char StartASCII = 0;
    for (char c : input)
    {
        char textChar = c - StartASCII;
        char keyChar = Key[keyIndex % Key.size()] - StartASCII;  
        output += VigenereSquare[textChar][keyChar];
        keyIndex++;
    }
}

void VigenereCipher::Decrypt(const std::string& input, std::string& output)
{
    output.clear();
    size_t keyIndex = 0;
    char StartASCII = 0;

    for (char c : input)
    {
        char codedChar = c - StartASCII;
        char keyChar = Key[keyIndex % Key.size()] - StartASCII;
        int originalChar = (codedChar - keyChar + ASCII) % ASCII;
        output += StartASCII + originalChar;
        keyIndex++;
    }
}

void VigenereCipher::GenerateVigenereSquare()
{
    int Shift = 0;
    std::string TempRow;
    for (int i = 0; i < ASCII; i++)
    {
        TempRow.clear();  
        for (int j = 0; j < ASCII; j++)
        {
            TempRow += static_cast<char>(j);  
        }
        std::rotate(TempRow.begin(), TempRow.begin() + Shift, TempRow.end());
        for (int j = 0; j < ASCII; j++)
        {
            VigenereSquare[i][j] = TempRow[j]; 
        }
        Shift++;  
    }
}

void VigenereCipher::printVigenereSquare()
{
    for (int i = 0; i < ASCII; ++i)
    {
        for (int j = 0; j < ASCII; ++j)
        {
            std::cout << VigenereSquare[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool VigenereCipher::isASCII(const std::string& text)
{
    return std::all_of(text.begin(), text.end(), [](unsigned char c) 
    {
        return c >= 0 && c < ASCII; 
    });
}
