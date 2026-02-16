# HF Tokenizers C++

A C++ wrapper for the [Hugging Face Tokenizers](https://github.com/huggingface/tokenizers) library, using C FFI for high-performance tokenization in C++.

## Features

- **Blazing Fast**: Uses the Rust `tokenizers` core library.
- **Easy Integration**: Simple C++ interface via `tokenizers.h`.
- **Automated Build**: CMake automatically handles Rust compilation and submodule management.
- **C++23 Ready**: Built using modern C++ standards.

## Prerequisites

Before building, ensure you have the following installed:

- **C++ Compiler**: Supporting C++23 (e.g., GCC 14+, Clang 18+).
- **CMake**: Version 3.10 or higher.
- **Rust & Cargo**: Required to build the underlying tokenizers library.
- **Git**: For managing submodules.

## Getting Started

### 1. Clone the Repository

```bash
git clone --recursive https://github.com/your-repo/hf_tokenizers_cpp.git
cd hf_tokenizers_cpp
```

### 2. Build the Project

The CMake build system is configured to automatically synchronize submodules and build the Rust library in release mode.

```bash
mkdir build && cd build
cmake ..
make
```

### 3. Usage Example

To test the tokenizer, you need a `tokenizer.json` file (e.g., from GPT-2).

#### Download a Tokenizer
```bash
wget https://huggingface.co/openai-community/gpt2/resolve/main/tokenizer.json
```

#### Run the Example
```bash
./hf_tokenizers_cpp tokenizer.json
```

## API Overview

The project provides a C-compatible FFI layer defined in `tokenizers.h`. Here is a basic example of how to use it in C++:

```cpp
#include "tokenizers.h"
#include <iostream>
#include <vector>

int main() {
    // Load your tokenizer JSON bytes
    // ... read file into buffer ...
    
    TokenizerHandle* tokenizer = tokenizer_new_from_json(json_bytes, size);
    if (!tokenizer) return 1;

    // Encode text
    const char* text = "Hello, world!";
    char* encoded_json = tokenizer_encode(tokenizer, text);
    
    std::cout << "Encoded: " << encoded_json << std::endl;

    // Cleanup
    string_free(encoded_json);
    tokenizer_free(tokenizer);
    
    return 0;
}
```

## Project Structure

- `main.cpp`: Entry point and usage example.
- `tokenizers.h`: C FFI header definition.
- `tokenizers/`: Submodule containing the Hugging Face Rust implementation.
- `CMakeLists.txt`: Build configuration for both C++ and Rust.

## License

This project is licensed under the Apache-2.0 License - see the LICENSE file for details.
