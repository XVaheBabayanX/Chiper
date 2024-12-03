#include "SimpleSubstitution.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

SimpleSubstitutionCipher::SimpleSubstitutionCipher()
{
    GenerateRandomAlphabet(); 
    GenerateReverseAlphabet();
}

SimpleSubstitutionCipher::SimpleSubstitutionCipher(const std::string& key)
{
    setKey(key);
}

void SimpleSubstitutionCipher::setKey(const std::string& key)
{
    std::string modifiedKey = key;
    removeDuplicates(modifiedKey);
    Key = modifiedKey;
    GenerateAlphabet();
    GenerateReverseAlphabet();
}


std::string SimpleSubstitutionCipher::getKey() const
{
    return Key;
}

void SimpleSubstitutionCipher::printAlphabet() const
{
    for (size_t i = 0; i < ASCII; i++)
    {
        std::cout << Alphabet[i] << " ";
    }
}

void SimpleSubstitutionCipher::removeDuplicates(std::string& text)
{
    std::string result;
    std::unordered_set<char> seen;

    for (char c : text)
    {
        if (!seen.count(c))
        {
            result += c;
            seen.insert(c);
        }
    }

    text = result;
}

void SimpleSubstitutionCipher::GenerateAlphabet()
{
    Alphabet.resize(ASCII);
    std::vector<bool> used(ASCII, false);

    if (!Key.empty())
    {
        for (size_t i = 0; i < Key.size(); i++)
        {
            Alphabet[i] = Key[i];
            used[static_cast<unsigned char>(Key[i])] = true;
        }
    }

    size_t index = Key.size();
    for (size_t i = 0; i < ASCII; i++)
    {
        if (!used[i])
        {
            Alphabet[index++] = static_cast<char>(i);
        }
    }
}

void SimpleSubstitutionCipher::GenerateReverseAlphabet()
{
    reverseAlphabet.clear();
    for (size_t i = 0; i < ASCII; i++)
    {
        reverseAlphabet[Alphabet[i]] = static_cast<char>(i);
    }
}

void SimpleSubstitutionCipher::GenerateRandomAlphabet()
{
    Alphabet.resize(ASCII);
    for (int i = 0; i < ASCII; i++)
    {
        Alphabet[i] = static_cast<char>(i);
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(Alphabet.begin(), Alphabet.end(), generator);
}

void SimpleSubstitutionCipher::Encrypt(const std::string& OriginalText, std::string& EncryptedText)
{
    size_t text_length = OriginalText.length();
    EncryptedText.resize(text_length);

    for (size_t i = 0; i < text_length; i++)
    {
        EncryptedText[i] = Alphabet[static_cast<unsigned char>(OriginalText[i])];
    }
}

void SimpleSubstitutionCipher::Decrypt(const std::string& EncryptedText, std::string& DecryptedText)
{
    size_t text_length = EncryptedText.length();
    DecryptedText.resize(text_length);

    for (size_t i = 0; i < text_length; i++)
    {
        DecryptedText[i] = reverseAlphabet[EncryptedText[i]];
    }
}
