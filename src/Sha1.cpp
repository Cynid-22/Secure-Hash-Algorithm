#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include "common.h"

using namespace std;

// SHA-1 Circular Rotate Left
inline uint32_t leftRotate(uint32_t x, uint32_t c) {
    return (x << c) | (x >> (32 - c));
}

// Process a single 64-byte block
void transform(const uint8_t* block, uint32_t& h0, uint32_t& h1, uint32_t& h2, uint32_t& h3, uint32_t& h4) {
    uint32_t w[80];

    // Break chunk into sixteen 32-bit big-endian words
    for (int j = 0; j < 16; ++j) {
        w[j] = (block[j * 4] << 24) |
               (block[j * 4 + 1] << 16) |
               (block[j * 4 + 2] << 8) |
               (block[j * 4 + 3]);
    }

    // Extend to 80 words
    for (int j = 16; j < 80; ++j) {
        w[j] = leftRotate(w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16], 1);
    }

    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;
    uint32_t e = h4;

    // Unrolled loops
    // Round 1: 0-19
    for (int j = 0; j < 20; ++j) {
        uint32_t f = (b & c) | ((~b) & d);
        uint32_t k = 0x5A827999;
        uint32_t temp = leftRotate(a, 5) + f + e + k + w[j];
        e = d; d = c; c = leftRotate(b, 30); b = a; a = temp;
    }

    // Round 2: 20-39
    for (int j = 20; j < 40; ++j) {
        uint32_t f = b ^ c ^ d;
        uint32_t k = 0x6ED9EBA1;
        uint32_t temp = leftRotate(a, 5) + f + e + k + w[j];
        e = d; d = c; c = leftRotate(b, 30); b = a; a = temp;
    }

    // Round 3: 40-59
    for (int j = 40; j < 60; ++j) {
        uint32_t f = (b & c) | (b & d) | (c & d);
        uint32_t k = 0x8F1BBCDC;
        uint32_t temp = leftRotate(a, 5) + f + e + k + w[j];
        e = d; d = c; c = leftRotate(b, 30); b = a; a = temp;
    }

    // Round 4: 60-79
    for (int j = 60; j < 80; ++j) {
        uint32_t f = b ^ c ^ d;
        uint32_t k = 0xCA62C1D6;
        uint32_t temp = leftRotate(a, 5) + f + e + k + w[j];
        e = d; d = c; c = leftRotate(b, 30); b = a; a = temp;
    }

    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
}

int main(int argc, char* argv[]) {
    initBinaryMode();
    
    // Check for file size argument
    size_t totalExpectedSize = 0;
    if (argc > 1) {
        try {
            totalExpectedSize = std::stoull(argv[1]);
        } catch (...) {
            totalExpectedSize = 0;
        }
    }
    
    // State variables
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;
    
    uint64_t totalBytes = 0;
    uint8_t buffer[64];
    
    // Report initial progress
    if (totalExpectedSize > 0) reportProgress(0, totalExpectedSize);
    
    // Read from stdin in 64-byte chunks
    while (cin.read((char*)buffer, 64)) {
        totalBytes += 64;
        transform(buffer, h0, h1, h2, h3, h4);
        
        // Report progress periodically
        if (totalExpectedSize > 0) {
            reportProgress(totalBytes, totalExpectedSize);
        }
    }
    
    // Handle remaining bytes
    size_t bytesRead = cin.gcount();
    totalBytes += bytesRead;
    
    // Padding logic (same structure as MD5 but big-endian length)
    uint8_t finalBlock[128];
    memset(finalBlock, 0, 128);
    memcpy(finalBlock, buffer, bytesRead);
    
    finalBlock[bytesRead] = 0x80;
    
    uint64_t totalBits = totalBytes * 8;
    
    if (bytesRead < 56) {
        // Fits in one block
        // Append length at bytes 56-63 (Big Endian)
        for (int i = 7; i >= 0; --i) {
            finalBlock[56 + (7-i)] = (totalBits >> (i * 8)) & 0xFF;
        }
        transform(finalBlock, h0, h1, h2, h3, h4);
    } else {
        // Need two blocks
        transform(finalBlock, h0, h1, h2, h3, h4);
        
        memset(finalBlock, 0, 64);
        // Length at bytes 56-63 of second block (Big Endian)
        for (int i = 7; i >= 0; --i) {
            finalBlock[56 + (7-i)] = (totalBits >> (i * 8)) & 0xFF;
        }
        transform(finalBlock, h0, h1, h2, h3, h4);
    }

    // Output
    uint32_t result[5] = {h0, h1, h2, h3, h4};
    for (int i = 0; i < 5; ++i) {
        cout << hex << setfill('0') << setw(8) << result[i];
    }
    cout.flush();
    cout << endl;
    
    return 0;
}
