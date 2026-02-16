#include "tokenizers.h"
#include <iostream>
#include <cstring>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << "=== Tokenizers C FFI Example ===" << std::endl;
    std::cout << "\nThis example demonstrates the C FFI bindings for the tokenizers library." << std::endl;

    // Note: For a working example, you need a valid tokenizer JSON configuration
    // You can obtain one from:
    // - A pretrained model (requires HTTP feature and network access)
    // - A tokenizer.json file from Hugging Face model hub

    if (argc > 1) {
        // If a tokenizer file is provided as argument, use it
        std::string filename = argv[1];
        std::cout << "\nAttempting to load tokenizer from: " << filename << std::endl;

        FILE* file = fopen(filename.c_str(), "rb");
        if (!file) {
            std::cerr << "Error: Could not open file: " << filename << std::endl;
            return 1;
        }

        // Read file size
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Read file contents
        char* json_buffer = new char[file_size];
        size_t read_size = fread(json_buffer, 1, file_size, file);
        fclose(file);

        if (read_size != file_size) {
            std::cerr << "Error: Failed to read complete file" << std::endl;
            delete[] json_buffer;
            return 1;
        }

        std::cout << "\nCreating tokenizer from file (" << file_size << " bytes)..." << std::endl;

        TokenizerHandle* tokenizer = tokenizer_new_from_json(
            reinterpret_cast<const uint8_t*>(json_buffer),
            file_size
        );

        delete[] json_buffer;

        if (!tokenizer) {
            std::cerr << "Error: Failed to create tokenizer" << std::endl;
            return 1;
        }

        std::cout << "✓ Tokenizer created successfully" << std::endl;

        // Get vocabulary size
        std::cout << "\nVocabulary size: " << tokenizer_get_vocab_size(tokenizer) << std::endl;
        // Encode a sample string
        const char* sample_text = "Hello, world!";
        char* encoded = tokenizer_encode(tokenizer, sample_text);
        if (encoded) {
            std::cout << "\nEncoded '" << sample_text << "' to: " << encoded << std::endl;
            string_free(encoded);
        } else {
            std::cerr << "Error: Failed to encode text" << std::endl;
        }

        // Clean up
        tokenizer_free(tokenizer);
        std::cout << "✓ Tokenizer freed successfully" << std::endl;

    } else {
        // Demonstrate the FFI without a valid tokenizer
        std::cout << "\n=== C FFI Functions Available ===" << std::endl;
        std::cout << "1. tokenizer_new_from_json() - Create tokenizer from JSON" << std::endl;
        std::cout << "2. tokenizer_free() - Free tokenizer handle" << std::endl;
        std::cout << "3. tokenizer_encode() - Encode text to tokens" << std::endl;
        std::cout << "4. tokenizer_decode() - Decode token IDs to text" << std::endl;
        std::cout << "5. tokenizer_get_vocab_size() - Get vocabulary size" << std::endl;
        std::cout << "6. tokenizer_id_to_token() - Convert ID to token string" << std::endl;
        std::cout << "7. tokenizer_token_to_id() - Convert token string to ID" << std::endl;
        std::cout << "8. string_free() - Free strings returned from FFI" << std::endl;

        std::cout << "\n=== Usage ===" << std::endl;
        std::cout << "To test with a real tokenizer, run:" << std::endl;
        std::cout << "  " << argv[0] << " /path/to/tokenizer.json" << std::endl;

        std::cout << "\n=== To Get a Tokenizer File ===" << std::endl;
        std::cout << "1. Download from Hugging Face: https://huggingface.co/models" << std::endl;
        std::cout << "2. Look for 'tokenizer.json' in the model repository" << std::endl;
        std::cout << "3. Run: " << argv[0] << " tokenizer.json" << std::endl;

        std::cout << "\n=== FFI Binding Example ===" << std::endl;
        std::cout << "C++:\n"
                  << "    TokenizerHandle* tok = tokenizer_new_from_json(bytes, len);\n"
                  << "    char* result = tokenizer_encode(tok, \"hello world\");\n"
                  << "    tokenizer_free(tok);\n" << std::endl;
    }

    std::cout << "=== Example completed ===" << std::endl;
    return 0;
}

