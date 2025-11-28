#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>

// Platform-specific includes for binary mode
#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>
#endif

// Initialize stdin to binary mode to prevent corruption of binary data
inline void initBinaryMode() {
    #ifdef _WIN32
        _setmode(_fileno(stdin), _O_BINARY);
    #endif
}

// Read all input from stdin
inline std::string readStdinToString() {
    return std::string((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
}

#endif
