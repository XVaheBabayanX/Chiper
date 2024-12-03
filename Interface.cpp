#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Cipher.h"
#include <filesystem>

namespace fs = std::filesystem;

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

void Write(MyMode mode, MyFile inputType, std::string outputPath, std::string output)
{
    if (mode == MyMode::ENCRYPT)
    {
        if (inputType == MyFile::Text)
        {
            std::cout << "Encrypted Text: " << output << "\n";
        }
        else if (inputType == MyFile::File)
        {
            std::ofstream outputFile(outputPath, std::ios::out);
            if (!outputFile)
            {
                std::cerr << "Failed to open output file.\n";
            }
            outputFile << output;
            outputFile.close();
            std::cout << "File encrypted successfully.\n";
        }
    }
    else if (mode == MyMode::DECRYPT)
    {
        if (inputType == MyFile::Text)
        {
            std::cout << "Decrypted Text: " << output << "\n";
        }
        else if (inputType == MyFile::File)
        {
            std::ofstream outputFile(outputPath, std::ios::out);
            if (!outputFile)
            {
                std::cerr << "Failed to open output file.\n";
            }
            outputFile << output;
            outputFile.close();
            std::cout << "File decrypted successfully.\n";
        }
    }
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

    std::string inputPath = "Text";
    std::string outputPath = "Text";

    MyMode mode;
    MyCipher algorithm;

    std::cout << "Input argument: " << inputArg << "\n";
    MyFile inputType = (inputArg.find('.') != std::string::npos && outputArg.find('.') != std::string::npos) ? MyFile::File : MyFile::Text;
    std::cout << "Determined input type: "
        << (inputType == MyFile::File ? "File" : "Text") << "\n";

    if(inputType == MyFile::File)
    {
        std::string inputPath = convertPathToDoubleSlashes(inputArg);
        std::string outputPath = convertPathToDoubleSlashes(outputArg);
        //inputPath = inputArg;
        //outputPath = outputArg;
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
    }

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
        std::string Original, Encrypted;
        if (inputType == MyFile::Text)
        {
            std::cout << "Input Text: ";
            std::getline(std::cin, Original);
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
            Original = fileContent;
        }
        switch (algorithm)
        {
        case MyCipher::Caesar:
        {
            size_t Shift;
            std::cout << "Input Shift: ";
            std::cin >> Shift;
            cipher.caesar()->setShift(Shift);
            cipher.caesar()->Encrypt(Original, Encrypted);
            Write(mode, inputType, outputPath, Encrypted);
            break;
        }
        case MyCipher::Polybius:
        {
            std::string Key;
            std::cout << "Input Key: ";
            std::getline(std::cin, Key);
            cipher.polybius()->setKey(Key);
            cipher.polybius()->Encrypt(Original, Encrypted);
            Write(mode, inputType, outputPath, Encrypted);
            break;
        }
        case MyCipher::SimpleSubstitution:
        {
            std::string Key;
            std::cout << "Input Key: ";
            std::getline(std::cin, Key);
            cipher.simplesubstitution()->setKey(Key);
            cipher.simplesubstitution()->Encrypt(Original, Encrypted);
            Write(mode, inputType, outputPath, Encrypted);
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
            Write(mode, inputType, outputPath, Encrypted);
            break;
        }
        case MyCipher::Vigenere:
        {
            std::string Key;
            std::cout << "Input Key: ";
            std::getline(std::cin, Key);
            cipher.vigenere()->setKey(Key);
            cipher.vigenere()->Encrypt(Original, Encrypted);
            Write(mode, inputType, outputPath, Encrypted);
            break;
        }
        default:
            std::cerr << "Cipher not implemented for encryption.\n";
            return 1;
        }
    }
    else if (mode == MyMode::DECRYPT)
    {
        std::string Encrypted, Decrypted;
        if (inputType == MyFile::Text)
        {
            std::cout << "Input Encrypted Text: ";
            std::getline(std::cin, Encrypted);
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
            Encrypted = fileContent;

        }
        switch (algorithm)
        {
        case MyCipher::Caesar:
        {
            size_t Shift;
            std::cout << "Input Shift: ";
            std::cin >> Shift;
            cipher.caesar()->setShift(Shift);
            cipher.caesar()->Decrypt(Encrypted, Decrypted);
            Write(mode, inputType, outputPath, Decrypted);
            break;
        }
        case MyCipher::Polybius:
        {
            std::string Key;
            std::cout << "Input Key: ";
            std::getline(std::cin, Key);
            cipher.polybius()->setKey(Key);
            cipher.polybius()->Decrypt(Encrypted, Decrypted);
            Write(mode, inputType, outputPath, Decrypted);
            break;
        }
        case MyCipher::SimpleSubstitution:
        {
            std::string Key;
            std::cout << "Input Key: ";
            std::getline(std::cin, Key);
            cipher.simplesubstitution()->setKey(Key);
            cipher.simplesubstitution()->Decrypt(Encrypted, Decrypted);
            Write(mode, inputType, outputPath, Decrypted);
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
            Write(mode, inputType, outputPath, Decrypted);
            break;
        }
        case MyCipher::Vigenere:
        {
            std::string Key;
            std::cout << "Input Key: ";
            std::getline(std::cin, Key);
            cipher.vigenere()->setKey(Key);
            cipher.vigenere()->Decrypt(Encrypted, Decrypted);
            Write(mode, inputType, outputPath, Decrypted);
            break;
        }
        default:
            std::cerr << "Cipher not implemented for decryption.\n";
            return 1;
        }
    }

    return 0;
}