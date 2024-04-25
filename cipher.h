#ifndef CIPHER_H
#define CIPHER_H

#include <ctype.h> // for isalpha and islower functions

// Function to apply the Caesar cipher on a character
char caesar_cipher(char ch, int shift);

// Function to process the file for encryption or decryption
void process_file(const char *input_path, const char *output_path, int shift, char mode);

// Function for the Substitution cipher
char substitution_cipher(char ch, const char *key, int decrypt);

// Function to generate the Substitution key
void generate_substitution_key(char *key, const char *seed);

// Function to apply the Rail Fence cipher for encryption
char* rail_fence_cipher_encrypt(const char *plaintext, int rails);

// Function to apply the Rail Fence cipher for decryption
char* rail_fence_cipher_decrypt(const char *ciphertext, int rails);

#endif /* CIPHER_H */

/* CIPHER_H */
/*
DECLARE function cipher that takes a character and an integer shift
DECLARE function process_file that takes two string paths (input and output) and an integer shift
*/
