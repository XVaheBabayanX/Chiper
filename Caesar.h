#pragma 

#include "Crypto.h"

class CaesarCipher : public Crypto
{
private:
    std::string Key;
    size_t shift;
    static const size_t ASCII = 256;
    static const size_t SHIFT = 0;

public:
    CaesarCipher();
    CaesarCipher(size_t s);
    void setShift(size_t s);
    void Encrypt(const std::string& OriginalText, std::string& EncryptedText) override;
    void Decrypt(const std::string& EncryptedText, std::string& DecryptedText) override;

private:
    void Shift(size_t shift);
};