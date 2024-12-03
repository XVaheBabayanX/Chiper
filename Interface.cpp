#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Cipher.h"
#include "Compressor.h"

enum class MyMode
{
    ENCRYPT,
    DECRYPT,
    COMPRESS,
    DECOMPRESS
};

enum class MyCipher
{
    Caesar,
    Polybius,
    SimpleSubstitution,
    Transposition,
    Vigenere,
    LZ77,
    RLE,
    Huffman
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
    std::string text, action;
    if (mode == MyMode::ENCRYPT)
    {
        text = "Encrypted";
        action = "encrypted";
    }
    else if (mode == MyMode::DECRYPT)
    {
        text = "Decrypted";
        action = "decrypted";
    }
    else if (mode == MyMode::COMPRESS)
    {
        text = "Compressed";
        action = "compressed";
    }
    else if (mode == MyMode::DECOMPRESS)
    {
        text = "Decompressed";
        action = "decompressed";
    }

    if (inputType == MyFile::Text)
    {
        std::cout << text <<" Text: " << output << "\n";
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
        std::cout << "File "<< action <<" successfully.\n";
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

    MyFile inputType = (inputArg.find('.') != std::string::npos && outputArg.find('.') != std::string::npos) ? MyFile::File : MyFile::Text;

    if(inputType == MyFile::File)
    {
        inputPath = convertPathToDoubleSlashes(inputArg);
        outputPath = convertPathToDoubleSlashes(outputArg);
        std::cout << "Input path: " << inputPath << "\n";
        std::cout << "Output path: " << outputPath << "\n";
    }

    if (modeArg == "encrypt")
        mode = MyMode::ENCRYPT;
    else if (modeArg == "decrypt")
        mode = MyMode::DECRYPT;
    else if (modeArg == "compress")
        mode = MyMode::COMPRESS;
    else if (modeArg == "decompress")
        mode = MyMode::DECOMPRESS;
    else
    {
        std::cerr << "Invalid mode! Use 'encrypt', 'decrypt', 'compress' or 'decompress'.\n";
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
    else if (cipherArg == "lz77")
        algorithm = MyCipher::LZ77;
    else if (cipherArg == "rle")
        algorithm = MyCipher::RLE;
    else if (cipherArg == "huffman")
        algorithm = MyCipher::Huffman;
    else
    {
        std::cerr << "Invalid cipher! Use 'caesar', 'polybius', 'simple', 'transposition', 'vigenere', 'lz77', 'rle' or 'huffman'.\n";
        return 1;
    }

    Cipher cipher;
    Compressor compressor;

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
            if (!inputFile.is_open())
            {
                std::cerr << "Input file does not exist: " << inputPath << "\n";
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
            if (!inputFile.is_open())
            {
                std::cerr << "Input file does not exist: " << inputPath << "\n";
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
    else if (mode == MyMode::COMPRESS)
    {
        std::string Original, Compressed;
        if (inputType == MyFile::Text)
        {
            std::cout << "Input Text: ";
            std::getline(std::cin, Original);
        }
        else if (inputType == MyFile::File)
        {
            std::ifstream inputFile(inputPath, std::ios::in);
            if (!inputFile.is_open())
            {
                std::cerr << "Input file does not exist: " << inputPath << "\n";
                return 1;
            }
            std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            inputFile.close();
            Original = fileContent;
        }
        switch (algorithm)
        {
        case MyCipher::LZ77:
        {
            compressor.lz77()->Compress(Original, Compressed);
            Write(mode, inputType, outputPath, Compressed);
            break;
        }
        case MyCipher::RLE:
        {
            compressor.rle()->Compress(Original, Compressed);
            Write(mode, inputType, outputPath, Compressed);
            break;
        }
        case MyCipher::Huffman:
        {
            compressor.huffman()->Compress(Original, Compressed);
            //compressor.huffman()->printTree();
            Write(mode, inputType, outputPath, Compressed);
            break;
        }
        default:
            std::cerr << "Compressor not implemented for compression.\n";
            return 1;
        }
    }
    else if (mode == MyMode::DECOMPRESS)
    {
        std::string Compressed, Decompressed;
        if (inputType == MyFile::Text)
        {
            std::cout << "Input Compressed Text: ";
            std::getline(std::cin, Compressed);
        }
        else if (inputType == MyFile::File)
        {
            std::ifstream inputFile(inputPath, std::ios::in);
            if (!inputFile.is_open())
            {
                std::cerr << "Input file does not exist: " << inputPath << "\n";
                return 1;
            }
            std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            inputFile.close();
            Compressed = fileContent;
        }
        switch (algorithm)
        {
        case MyCipher::LZ77:
        {
            compressor.lz77()->Decompress(Compressed, Decompressed);
            Write(mode, inputType, outputPath, Decompressed);
            break;
        }
        case MyCipher::RLE:
        {
            compressor.rle()->Decompress(Compressed, Decompressed);
            Write(mode, inputType, outputPath, Decompressed);
            break;
        }
        case MyCipher::Huffman:
        {
            std::string inputTree;
            std::cout << "Enter pairs of (character, frequency) separated by commas (e.g., A5,B3,C2,D1): ";
            std::getline(std::cin, inputTree);
            compressor.huffman()->setTreeFromInput(inputTree);
            //compressor.huffman()->printTree();
            compressor.huffman()->Decompress(Compressed, Decompressed);
            Write(mode, inputType, outputPath, Decompressed);
            break;
        }
        default:
            std::cerr << "Compressor not implemented for decompression.\n";
            return 1;
        }
    }

    return 0;
}