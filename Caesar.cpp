#include "Caesar.h"

CaesarCipher::CaesarCipher() : CaesarCipher(SHIFT) {}

CaesarCipher::CaesarCipher(size_t s) : shift(s)
{
    Key.resize(ASCII); 
    Shift(shift);
}

void CaesarCipher::setShift(size_t s)
{
    s %= ASCII;
    shift = s;
    Shift(shift);
}

void CaesarCipher::Encrypt(const std::string& OriginalText, std::string& EncryptedText)
{
    size_t text_length = OriginalText.length();
    EncryptedText.resize(text_length);

    for (size_t i = 0; i < text_length; i++)
    {
        EncryptedText[i] = Key[static_cast<unsigned char>(OriginalText[i])];
    }
}

void CaesarCipher::Decrypt(const std::string& EncryptedText, std::string& DecryptedText)
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

void CaesarCipher::Shift(size_t shift)
{
    for (size_t i = 0; i < ASCII; i++)
    {
        Key[i] = static_cast<char>(i);
    }
    shift %= ASCII;
    std::rotate(Key.begin(), Key.begin() + (ASCII - shift), Key.end());
}
