//
// Created by rahim on 16/02/26.
//

#ifndef HF_TOKENIZERS_CPP_TOKENIZERS_H
#define HF_TOKENIZERS_CPP_TOKENIZERS_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Opaque handle for Tokenizer
     */
    typedef struct TokenizerHandle TokenizerHandle;

    /**
     * Create a new tokenizer from a JSON byte string
     * Returns a pointer to the tokenizer or null on error
     */
    struct TokenizerHandle *tokenizer_new_from_json(const uint8_t *json_bytes, uintptr_t json_len);

    /**
     * Free a tokenizer handle
     */
    void tokenizer_free(struct TokenizerHandle *handle);

    /**
     * Encode a string and return the result as JSON
     * Returns a C string that should be freed with string_free
     */
    char *tokenizer_encode(const struct TokenizerHandle *handle, const char *text);

    /**
     * Decode token IDs back to a string
     * Returns a C string that should be freed with string_free
     */
    char *tokenizer_decode(const struct TokenizerHandle *handle,
                           const uint32_t *ids,
                           uintptr_t ids_len);

    /**
     * Get the vocabulary size
     */
    uintptr_t tokenizer_get_vocab_size(const struct TokenizerHandle *handle);

    /**
     * Get a token from its ID
     * Returns a C string that should be freed with string_free
     */
    char *tokenizer_id_to_token(const struct TokenizerHandle *handle, uint32_t id);

    /**
     * Get a token's ID
     */
    uint32_t tokenizer_token_to_id(const struct TokenizerHandle *handle, const char *token);

    /**
     * Free a C string returned by tokenizer functions
     */
    void string_free(char *ptr);

#ifdef __cplusplus
}
#endif

#endif // HF_TOKENIZERS_CPP_TOKENIZERS_H
