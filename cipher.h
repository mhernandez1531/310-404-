#ifndef CIPHER_H
#define CIPHER_H

#include <ctype.h>

char cipher(char ch, int shift);
void process_file(const char *input_path, const char *output_path, int shift, char mode);
char* rail_fence_encrypt(const char* message, int rails);
char* rail_fence_decrypt(const char* message, int rails);
char substitution_cipher(char ch, const char *key, int decrypt);
void generate_substitution_key(char *key, const char *seed);

#endif /* CIPHER_H */


 /* CIPHER_H */
/*
DECLARE function cipher that takes a character and an integer shift
DECLARE function process_file that takes two string paths (input and output) and an integer shift
*/
