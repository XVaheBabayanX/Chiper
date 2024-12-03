#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Cipher.h"
#include <filesystem>
namespace fs = std::filesystem;

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

std::string convertPathToDoubleSlashes(const std::string& path) {
    std::string convertedPath = path;
    size_t pos = 0;
    while ((pos = convertedPath.find('\\', pos)) != std::string::npos) {
        convertedPath.insert(pos, "\\");
        pos += 2; 
    }
    return convertedPath;
}

int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        std::cerr << "Usage: program <mode> <algorithm> <file or text>\n";
        return 1;
    }

    std::string modeArg = argv[1];
    std::string cipherArg = argv[2];
    std::string inputArg = argv[3];
    std::string outputArg = argv[4];

    MyMode mode;
    MyCipher algorithm;

    std::cout << "Input argument: " << inputArg << "\n";
    MyFile inputType = (inputArg.find('.') != std::string::npos && outputArg.find('.') != std::string::npos) ? MyFile::File : MyFile::Text;
    std::cout << "Determined input type: "
        << (inputType == MyFile::File ? "File" : "Text") << "\n";

    //std::string inputPath = convertPathToDoubleSlashes(inputArg);
    //std::string outputPath = convertPathToDoubleSlashes(outputArg);
    std::string inputPath = inputArg;
    std::string outputPath = outputArg;
    std::cout << "Input path: " << inputPath << "\n";
    std::cout << "Output path: " << outputPath << "\n";
       
    //if (!fs::exists(inputPath)) {
    //    std::cerr << "File does not exist: " << inputPath << std::endl;
    //    return 1;
    //}
    //if (!fs::is_regular_file(inputPath)) {
    //    std::cerr << "Path exists but is not a file: " << inputPath << std::endl;
    //    return 1;
    //}

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

    Cipher cipher;

    if (mode == MyMode::ENCRYPT)
    {
        if (inputType == MyFile::Text)
        {
            std::string Original, Encrypted;
            std::cout << "Input Text: ";
            std::getline(std::cin, Original);

            switch (algorithm)
            {
            case MyCipher::Caesar:
            {
                size_t Shift;
                std::cout << "Input Shift: ";
                std::cin >> Shift;
                cipher.caesar()->setShift(Shift);
                cipher.caesar()->Encrypt(Original, Encrypted);
                std::cout << "Encrypted Text: " << Encrypted << "\n";
                break;
            }
            case MyCipher::Polybius:
            {
                std::string Key;
                std::cout << "Input Key: ";
                std::getline(std::cin, Key);
                cipher.polybius()->setKey(Key);
                cipher.polybius()->Encrypt(Original, Encrypted);
                std::cout << "Encrypted Text: " << Encrypted << "\n";
                break;
            }
            case MyCipher::SimpleSubstitution:
            {
                std::string Key;
                std::cout << "Input Key: ";
                std::getline(std::cin, Key);
                cipher.simplesubstitution()->setKey(Key);
                cipher.simplesubstitution()->Encrypt(Original, Encrypted);
                std::cout << "Encrypted Text: " << Encrypted << "\n";
                break;
            }
            case MyCipher::Transposition:
            {
                size_t Key;
                do {
                    std::cout << "Input key (0 for random key) Values( 1 - " << Original.size() << " ) : ";
                    std::cin >> Key;
                } while (Key > Original.size());

                if (Key == 0) {
                    Key = cipher.transposition()->GenerateRandomKey(Original.size());
                    std::cout << "Generated random key: " << Key << std::endl;
                }

                if (Key == 0) {
                    std::cerr << "Key cannot be 0." << std::endl;
                    return 1;
                }
                cipher.transposition()->setKey(Key);
                cipher.transposition()->Encrypt(Original, Encrypted);
                std::cout << "Encrypted Text: " << Encrypted << "\n";
                break;
            }
            case MyCipher::Vigenere:
            {
                std::string Key;
                std::cout << "Input Key: ";
                std::getline(std::cin, Key);
                cipher.vigenere()->setKey(Key);
                cipher.vigenere()->Encrypt(Original, Encrypted);
                std::cout << "Encrypted Text: " << Encrypted << "\n";
                break;
            }
            default:
                std::cerr << "Cipher not implemented for encryption.\n";
                return 1;
            }
        }
        else if (inputType == MyFile::File)
        {
            std::ifstream inputFile(inputPath, std::ios::in);
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
            {
                std::cout << "Input Shift: ";
                std::cin >> Shift;
                cipher.caesar()->setShift(Shift);
                cipher.caesar()->Encrypt(fileContent, Encrypted);
                break;
            }
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
                std::cerr << "Cipher not implemented for file encryption.\n";
                return 1;
            }

            std::ofstream outputFile(outputPath, std::ios::out);
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
            std::string Encrypted, Decrypted;
            std::cout << "Input Encrypted Text: ";
            std::getline(std::cin, Encrypted);

            switch (algorithm)
            {
            case MyCipher::Caesar:
            {
                size_t Shift;
                std::cout << "Input Shift: ";
                std::cin >> Shift;
                cipher.caesar()->setShift(Shift);
                cipher.caesar()->Decrypt(Encrypted, Decrypted);
                std::cout << "Decrypted Text: " << Decrypted << "\n";
                break;
            }
            case MyCipher::Polybius:
            {
                std::string Key;
                std::cout << "Input Key: ";
                std::getline(std::cin, Key);
                cipher.polybius()->setKey(Key);
                cipher.polybius()->Decrypt(Encrypted, Decrypted);
                std::cout << "Decrypted Text: " << Decrypted << "\n";
                break;
            }
            case MyCipher::SimpleSubstitution:
            {
                std::string Key;
                std::cout << "Input Key: ";
                std::getline(std::cin, Key);
                cipher.simplesubstitution()->setKey(Key);
                cipher.simplesubstitution()->Decrypt(Encrypted, Decrypted);
                std::cout << "Decrypted Text: " << Decrypted << "\n";
                break;
            }
            case MyCipher::Transposition:
            {
                size_t Key;
                do {
                    std::cout << "Input key Values( 1 - " << Encrypted.size() << " ) : ";
                    std::cin >> Key;
                } while (Key > Encrypted.size());
                if (Key == 0) {
                    std::cerr << "Key cannot be 0." << std::endl;
                    return 1;
                }
                cipher.transposition()->setKey(Key);
                cipher.transposition()->Decrypt(Encrypted, Decrypted);
                std::cout << "Decrypted Text: " << Decrypted << "\n";
                break;
            }
            case MyCipher::Vigenere:
            {
                std::string Key;
                std::cout << "Input Key: ";
                std::getline(std::cin, Key);
                cipher.vigenere()->setKey(Key);
                cipher.vigenere()->Decrypt(Encrypted, Decrypted);
                std::cout << "Decrypted Text: " << Decrypted << "\n";
                break;
            }
            default:
                std::cerr << "Cipher not implemented for decryption.\n";
                return 1;
            }
        }
        else if (inputType == MyFile::File)
        {
            std::ifstream inputFile(inputPath, std::ios::in);
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
            {
                std::cout << "Input Shift: ";
                std::cin >> Shift;
                cipher.caesar()->setShift(Shift);
                cipher.caesar()->Decrypt(fileContent, Decrypted);
                break;
            }
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
                std::cerr << "Cipher not implemented for file decryption.\n";
                return 1;
            }

            std::ofstream outputFile(outputPath, std::ios::out);
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