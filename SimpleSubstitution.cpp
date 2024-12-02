#include "SimpleSubstitution.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

SimpleSubstitutionCipher::SimpleSubstitutionCipher()
{
    Key.resize(ASCII); 
    for (int i = 0; i < ASCII; i++)
    {
        Key[i] = static_cast<char>(i); 
    }

    GenerateRandomKey(); 
}

void SimpleSubstitutionCipher::GenerateRandomKey()
{
    srand(static_cast<unsigned int>(time(0)));
    std::random_shuffle(Key.begin(), Key.end());
}

void SimpleSubstitutionCipher::Encrypt(const std::string& OriginalText, std::string& EncryptedText)
{
    size_t text_length = OriginalText.length();
    EncryptedText.resize(text_length);

    for (size_t i = 0; i < text_length; i++)
    {
        EncryptedText[i] = Key[static_cast<unsigned char>(OriginalText[i])];
    }
}

void SimpleSubstitutionCipher::Decrypt(const std::string& EncryptedText, std::string& DecryptedText)
{
    size_t text_length = EncryptedText.length();
    DecryptedText.resize(text_length);

    for (size_t i = 0; i < text_length; i++)
    {
        for (size_t j = 0; j < ASCII; j++)
        {
            if (EncryptedText[i] == Key[j])
            {
                DecryptedText[i] = static_cast<char>(j);
                break;
            }
        }
    }
}
