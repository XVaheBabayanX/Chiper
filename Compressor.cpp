#include "Compressor.h"

Compressor::Compressor() : _LZ77(nullptr), _RLE(nullptr), _Huffman(nullptr) {}

bool Compressor::isASCII(const std::string& text) const
{
    return std::all_of(text.begin(), text.end(), [](unsigned char c)
        {
            return c >= 0 && c < ASCII;
        });
}

LZ77* Compressor::lz77()
{
    if (!_LZ77) _LZ77 = std::make_unique<LZ77>();
    return _LZ77.get();
}

RLE* Compressor::rle()
{
    if (!_RLE) _RLE = std::make_unique<RLE>();
    return _RLE.get();
}

Huffman* Compressor::huffman()
{
    if (!_Huffman) _Huffman = std::make_unique<Huffman>();
    return _Huffman.get();
}