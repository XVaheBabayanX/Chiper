#pragma once

#include "LZ77.h"
#include "RLE.h"
#include "Huffman.h"
#include <algorithm>
#include <vector>
#include <memory>

class Compressor
{
public:
    Compressor();
    bool isASCII(const std::string&) const;

    LZ77* lz77();
    RLE* rle();
    Huffman* huffman();

private:
    static const int ASCII = 256;

    std::unique_ptr<LZ77> _LZ77;
    std::unique_ptr<RLE> _RLE;
    std::unique_ptr<Huffman> _Huffman;
}; 
