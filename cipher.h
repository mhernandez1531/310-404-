#ifndef CIPHER_H
#define CIPHER_H

#include <ctype.h> // for isalpha and islower functions 

//function to apply the caesar cipher on a character 
char caesar_cipher(char ch, int shift);

//function to process the fie for encryption or decryption 
void process_file(const char *input_path, const char *output_path, int shift, char mode);

char substitution_cipher(char ch, const char *key, int decrypt);
void generate_substitution_key(char *key, const char *seed);




#endif

/* CIPHER_H */

/*
DECLARE function cipher that takes a character and an integer shift
DECLARE function process_file that takes two string paths (input and output) and an integer shift
*/
