# Secure Hash Algorithm GUI

A graphical interface for calculating **SHA-256**, **SHA-384**, **SHA-512**, and **CRC-32** hashes using optimized C++ implementations.

## Features

✅ **Multiple Algorithms** - SHA-256, SHA-384, SHA-512, and CRC-32  
✅ **Live Hashing** - Hash updates automatically as you type  
✅ **Text & Binary File Support** - Hash any type of file  
✅ **Cross-Platform** - Works on Windows, macOS, and Linux  
✅ **Modern GUI** - Clean interface with status indicators  
✅ **Clipboard Integration** - Copy hash results with one click  
✅ **Optimized C++ Backend** - Fast hash calculations using compiled executables

## Requirements

- **Python 3.6 or higher** (for the GUI)
- **C++ compiler** (g++ recommended) to compile the hash executables
- **tkinter** (usually comes pre-installed with Python)

## Installation

### Step 1: Clone or Download

Download all files from the repository.

### Step 2: Compile C++ Executables

Before running the GUI, compile the C++ hash implementations:

```bash
g++ -o Sha256.exe Sha256.cpp
g++ -o Sha384.exe Sha384.cpp
g++ -o Sha512.exe Sha512.cpp
g++ -o Crc.exe Crc.cpp
```

**Note:** On Linux/macOS, omit the `.exe` extension:
```bash
g++ -o Sha256 Sha256.cpp
g++ -o Sha384 Sha384.cpp
g++ -o Sha512 Sha512.cpp
g++ -o Crc Crc.cpp
```

And update `algorithms.json` to remove the `.exe` extension from the executable names.

### Step 3: Run the GUI

```bash
python gui.py
```

## Usage

### How to Use

1. **Select Algorithm** - Choose from SHA-256, SHA-384, SHA-512, or CRC-32
2. **Input Data** - Either:
   - Type or paste text directly (hash updates automatically), OR
   - Click "Browse File..." to load a file (text or binary)
3. **View Result** - The hash appears automatically in the "Digest" field
4. **Copy** - Click "Copy" to copy the hash to your clipboard
5. **Clear** - Click "Clear" to reset both input and output

### Example Hashes

For the string `"hello"`:

- **SHA-256**: `2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824`
- **SHA-384**: `59e1748777448c69de6b800d7a33bbfb9ff1b463e44354c3553bcdb9c666fa90125a3c79f90397bdf5f6a13de828684f`
- **SHA-512**: `9b71d224bd62f3785d96d46ad3ea3d73319bfbc2890caadae2dff72519673ca72323c3d99ba5c11d7c7acc6e14b8c5da0c4663475c2e5c3adef46f73bcdec043`
- **CRC-32**: `3610a686`

## Architecture

### GUI (Python)
The `gui.py` file provides the user interface using tkinter. It handles:
- User input and file selection
- Calling C++ executables via subprocess
- Displaying results and status
- Live hashing (updates on every keystroke)

### Hash Implementations (C++)
Each hash algorithm is implemented in C++:
- `Sha256.cpp` - SHA-256 implementation
- `Sha384.cpp` - SHA-384 implementation
- `Sha512.cpp` - SHA-512 implementation
- `Crc.cpp` - CRC-32 implementation

The executables read input from stdin and output the hash to stdout, allowing the GUI to communicate with them easily.

### Configuration
`algorithms.json` defines available algorithms and their corresponding executables:
```json
{
  "algorithms": [
    {
      "name": "SHA-256",
      "type": "executable",
      "executable": "Sha256.exe",
      "description": "SHA-256 (256-bit Secure Hash Algorithm)"
    },
    ...
  ]
}
```

## File Structure

```
Hashing-Algorithm/
├── gui.py              # Main GUI application (Python)
├── algorithms.json     # Algorithm configuration
├── Sha256.cpp          # SHA-256 C++ implementation
├── Sha384.cpp          # SHA-384 C++ implementation
├── Sha512.cpp          # SHA-512 C++ implementation
├── Crc.cpp             # CRC-32 C++ implementation
├── sha.h               # C++ header file
├── Sha256.exe          # Compiled SHA-256 executable (after compilation)
├── Sha384.exe          # Compiled SHA-384 executable (after compilation)
├── Sha512.exe          # Compiled SHA-512 executable (after compilation)
├── Crc.exe             # Compiled CRC-32 executable (after compilation)
└── README.md           # This file
```

## Benefits of C++ Backend

🚀 **Performance** - Optimized C++ implementations provide fast hash calculations  
🔧 **Separation of Concerns** - GUI handles UX, C++ handles computation  
📚 **Educational** - Demonstrates inter-process communication between Python and C++  
🎯 **Precision** - C++ implementations match reference standards exactly

## Security Note

The hash functions provided are cryptographic-quality (SHA-256/384/512) or checksum-quality (CRC-32) and suitable for:
- File integrity verification
- Checksum generation
- Digital signatures (SHA variants only)

**Note:** CRC-32 is NOT cryptographically secure and should only be used for error detection.

## Troubleshooting

### "Executable not found" Error
This means the C++ files haven't been compiled yet. Follow the compilation steps in the Installation section.

### Compilation Errors
- Make sure you have g++ installed: `g++ --version`
- Check that `sha.h` is in the same directory as the `.cpp` files

## License

This project is open source and available for educational purposes.

## Contributing

Feel free to submit issues or pull requests to improve this tool!
