#include "Cipher.h"

Cipher::Cipher() : _Caesar(nullptr), _Polybius(nullptr), _SimpleSubstitution(nullptr), _Transposition(nullptr), _Vigenere(nullptr) {}

std::vector<Crypto*> Cipher::getChiper()
{
    std::vector<Crypto*> chipers;
    if (_Caesar) chipers.push_back(_Caesar.get());
    if (_Polybius) chipers.push_back(_Polybius.get());
    if (_SimpleSubstitution) chipers.push_back(_SimpleSubstitution.get());
    if (_Transposition) chipers.push_back(_Transposition.get());
    if (_Vigenere) chipers.push_back(_Vigenere.get());
    return chipers;
}

CaesarCipher* Cipher::caesar()
{
    if (!_Caesar) _Caesar = std::make_unique<CaesarCipher>();
    return _Caesar.get();
}

PolybiusCipher* Cipher::polybius()
{
    if (!_Polybius) _Polybius = std::make_unique<PolybiusCipher>();
    return _Polybius.get();
}

SimpleSubstitutionCipher* Cipher::simplesubstitution()
{
    if (!_SimpleSubstitution) _SimpleSubstitution = std::make_unique<SimpleSubstitutionCipher>();
    return _SimpleSubstitution.get();
}

TranspositionCipher* Cipher::transposition()
{
    if (!_Transposition) _Transposition = std::make_unique<TranspositionCipher>();
    return _Transposition.get();
}

VigenereCipher* Cipher::vigenere()
{
    if (!_Vigenere) _Vigenere = std::make_unique<VigenereCipher>();
    return _Vigenere.get();
}

bool Cipher::setKey(const std::string& key)
{
    if (!isASCII(key)) return false;
    _Key = key;
    return true;
}

bool Cipher::isASCII(const std::string& text) const
{
    return std::all_of(text.begin(), text.end(), [](unsigned char c)
        {
            return c >= 0 && c < ASCII;
        });
}