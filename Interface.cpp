#include <iostream>
#include <string>
#include <fstream>
#include "Cipher.h"

const std::string YES = "y";
const std::string NO = "n";

enum class MyMode
{
    ENCRYPT,
    DECRYPT
};

enum class MyCipher
{
    Caesar,
    Polybius,
    SimpleSubstitution,
    Transposition,
    Vigenere
};

enum class MyFile
{
    File,
    Text
};

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: program <mode> <algorithm> <file or text>\n";
        return 1;
    }

    std::string modeArg = argv[1];
    std::string cipherArg = argv[2];
    std::string inputArg = argv[3];

    MyMode mode;
    MyCipher algorithm;
    MyFile inputType;

    if (modeArg == "encrypt")
        mode = MyMode::ENCRYPT;
    else if (modeArg == "decrypt")
        mode = MyMode::DECRYPT;
    else
    {
        std::cerr << "Invalid mode! Use 'encrypt' or 'decrypt'.\n";
        return 1;
    }

    if (cipherArg == "caesar")
        algorithm = MyCipher::Caesar;
    else if (cipherArg == "polybius")
        algorithm = MyCipher::Polybius;
    else if (cipherArg == "simple")
        algorithm = MyCipher::SimpleSubstitution;
    else if (cipherArg == "transposition")
        algorithm = MyCipher::Transposition;
    else if (cipherArg == "vigenere")
        algorithm = MyCipher::Vigenere;
    else
    {
        std::cerr << "Invalid cipher! Use 'caesar', 'polybius', 'simple', 'transposition', or 'vigenere'.\n";
        return 1;
    }

    if (inputArg == "text") {
        inputType = MyFile::Text;
    }
    else if (inputArg == "file") {
        inputType = MyFile::File;
    }
    else {
        std::cerr << "Invalid input type! Use 'text' or 'file'.\n";
        return 1;
    }


    Cipher cipher;

    if (mode == MyMode::ENCRYPT)
    {
        if (inputType == MyFile::Text)
        {
            std::string Original, Encrypted, Key;
            size_t Shift;
            std::cout << "Input Text: ";
            std::cin >> Original;

            switch (algorithm)
            {
            case MyCipher::Caesar:
                std::cout << "Input Shift: ";
                std::cin >> Shift;
                cipher.caesar()->setShift(Shift);
                cipher.caesar()->Encrypt(Original, Encrypted);
                std::cout << "Encrypted Text: " << Encrypted << "\n";
                break;
            case MyCipher::Polybius:
            {
                break;
            }
            case MyCipher::SimpleSubstitution:
            {
                break;
            }
            case MyCipher::Transposition:
            {
                break;
            }
            case MyCipher::Vigenere:
            {
                break;
            }
            default:
                std::cerr << "Cipher not implemented for encryption.\n";
                return 1;
            }
        }
        else if (inputType == MyFile::File)
        {
            std::ifstream inputFile(inputArg, std::ios::in);
            if (!inputFile)
            {
                std::cerr << "Failed to open input file.\n";
                return 1;
            }

            std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            inputFile.close();

            std::string Encrypted;
            size_t Shift;

            switch (algorithm)
            {
            case MyCipher::Caesar:
                std::cout << "Input Shift: ";
                std::cin >> Shift;
                cipher.caesar()->setShift(Shift);
                cipher.caesar()->Encrypt(fileContent, Encrypted);
                break;
            default:
                std::cerr << "Cipher not implemented for file encryption.\n";
                return 1;
            }

            std::ofstream outputFile(inputArg + ".enc", std::ios::out);
            if (!outputFile)
            {
                std::cerr << "Failed to open output file.\n";
                return 1;
            }

            outputFile << Encrypted;
            outputFile.close();
            std::cout << "File encrypted successfully.\n";
        }
    }
    else if (mode == MyMode::DECRYPT)
    {
        if (inputType == MyFile::Text)
        {
            std::string Encrypted, Decrypted, Key;
            size_t Shift;
            std::cout << "Input Text: ";
            std::cin >> Encrypted;
            switch (algorithm)
            {
            case MyCipher::Caesar:
                std::cout << "Input Shift: ";
                std::cin >> Shift;
                cipher.caesar()->setShift(Shift);
                cipher.caesar()->Decrypt(Encrypted, Decrypted);
                std::cout << "Decrypted Text: " << Decrypted << "\n";
                break;
            case MyCipher::Polybius:
            {
                break;
            }
            case MyCipher::SimpleSubstitution:
            {
                break;
            }
            case MyCipher::Transposition:
            {
                break;
            }
            case MyCipher::Vigenere:
            {
                break;
            }
            default:
                std::cerr << "Cipher not implemented for encryption.\n";
                return 1;
            }
        }
        else if (inputType == MyFile::File)
        {
            std::ifstream inputFile(inputArg, std::ios::in);
            if (!inputFile)
            {
                std::cerr << "Failed to open input file.\n";
                return 1;
            }

            std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            inputFile.close();

            std::string Decrypted;
            size_t Shift;

            switch (algorithm)
            {
            case MyCipher::Caesar:
                std::cout << "Input Shift: ";
                std::cin >> Shift;
                cipher.caesar()->setShift(Shift);
                cipher.caesar()->Decrypt(fileContent, Decrypted);
                break;
            default:
                std::cerr << "Cipher not implemented for file decryption.\n";
                return 1;
            }

            std::ofstream outputFile(inputArg + ".dec", std::ios::out);
            if (!outputFile)
            {
                std::cerr << "Failed to open output file.\n";
                return 1;
            }

            outputFile << Decrypted;
            outputFile.close();
            std::cout << "File decrypted successfully.\n";
        }
    }

    return 0;
}