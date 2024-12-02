#pragma once

#include "Caesar.h"
#include "Polybius.h"
#include "SimpleSubstitution.h"
#include "Transposition.h"
#include "Vigenere.h"
#include <vector>
#include <memory>

class Cipher
{
public:
    Cipher();

    bool setKey(const std::string&);
    bool isASCII(const std::string&) const;
    std::vector<Crypto*> getChiper();

    CaesarCipher* caesar();
    PolybiusCipher* polybius();
    SimpleSubstitutionCipher* simplesubstitution();
    TranspositionCipher* transposition();
    VigenereCipher* vigenere();

private:
    std::string _Key;
    static const int ASCII = 256;

    std::unique_ptr<CaesarCipher> _Caesar;
    std::unique_ptr<PolybiusCipher> _Polybius;
    std::unique_ptr<SimpleSubstitutionCipher> _SimpleSubstitution;
    std::unique_ptr<TranspositionCipher> _Transposition;
    std::unique_ptr<VigenereCipher> _Vigenere;
};