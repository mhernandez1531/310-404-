#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define ALPHABET_SIZE 26
#define DEFAULT_SEED "some_seed_string"

// Rail Fence Cipher Encryption
char* rail_fence_encrypt(const char* message, int rails) {
    int len = strlen(message);
    char* encrypted = (char*)malloc(len + 1);  // Allocate memory for the encrypted text
    if (!encrypted) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize the encrypted text with null characters
    for (int i = 0; i < len; i++) {
        encrypted[i] = '\0';
    }

    int rail_len = 2 * rails - 2;
    int k = 0;

    for (int i = 0; i < rails; i++) {
        for (int j = i; j < len; j += rail_len) {
            encrypted[k++] = message[j];
            if (i != 0 && i != rails - 1 && j + rail_len - 2 * i < len)
                encrypted[k++] = message[j + rail_len - 2 * i];
        }
    }
    encrypted[k] = '\0';  // Add the null terminator
    return encrypted;
}
/*
// Rail Fence Cipher Decryption
char* rail_fence_decrypt(const char* message, int rails) {
    int len = strlen(message);
    char* decrypted = (char*)malloc(len + 1);  // Allocate memory for the decrypted text
    if (!decrypted) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize the decrypted text with null characters
    for (int i = 0; i < len; i++) {
        decrypted[i] = '\0';
    }

    int rail_len = 2 * rails - 2;
    int k = 0;
    int cycle = 2 * (rails - 1);

    for (int i = 0; i < rails; i++) {
        for (int j = i; j < len; j += cycle) {
            decrypted[j] = message[k++];
            if (i != 0 && i != rails - 1 && j + cycle - 2 * i < len)
                decrypted[j + cycle - 2 * i] = message[k++];
        }
    }
    decrypted[len] = '\0';  // Add the null terminator
    return decrypted;
}
*/

char* rail_fence_decrypt(const char* message, int rails) {
    int len = strlen(message);
    char* decrypted = (char*)malloc(len + 1); // Allocate memory for the decrypted text
    if (!decrypted) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize the decrypted text with null characters
    memset(decrypted, '\0', len + 1);

    int* mark = (int*)calloc(len, sizeof(int)); // To mark visited positions in the message
    int k = 0, idx = 0;

    // Traverse through each rail
    for (int r = 0; r < rails; r++) {
        int pos = r;
        int down = 1; // Direction indicator: 1 for down, 0 for up
        while (pos < len) {
            if (mark[pos] == 0) { // If position is not yet visited
                decrypted[pos] = message[k++];
                mark[pos] = 1; // Mark this position as visited
            }

            // Calculate the next position
            if (r == 0 || r == rails - 1) { // First and last rails
                pos += 2 * (rails - 1);
            } else if (down) { // Middle rails going down
                pos += 2 * (rails - r - 1);
                down = 0; // Change direction to up
            } else { // Middle rails going up
                pos += 2 * r;
                down = 1; // Change direction to down
            }
        }
    }

    free(mark); // Free the used memory
    return decrypted; // Return the decrypted message
}



// Caesar Cipher Encryption and Decryption
char caesar_cipher(char ch, int shift) {
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';  // Base letter for lowercase or uppercase
        return (char)(((ch - base + shift) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE + base);
    }
    return ch;
}

// Substitution Cipher Encryption and Decryption
char substitution_cipher(char ch, const char *key, int decrypt) {
    if(isalpha(ch)){
        int index = toupper(ch) - 'A';
        if(decrypt){
            const char *pos = strchr(key, toupper(ch));
            return(pos ? 'A' + (pos - key) : ch) + (islower(ch) ? 32 : 0);
        } else {
            return key[index] + (islower(ch) ? 32 : 0);
        }
    }
    return ch;
}

// Generate Substitution Cipher Key
void generate_substitution_key(char *key, const char *seed){
    char standard_alphabet[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    strcpy(key, standard_alphabet);
    int seed_length = strlen(seed);
    for(int i = 0; i < ALPHABET_SIZE; i++){
        int j = (seed[i % seed_length] + i) % ALPHABET_SIZE;
        char temp = key[i];
        key[i] = key[j];
        key[j] = temp;
    }
}

// Process File using Caesar or Substitution Cipher
void process_file(const char *input_path, const char *output_path, int shift, char mode) {
    FILE *input = fopen(input_path, "r");
    FILE *output = fopen(output_path, "w");

    if (!input || !output) {
        fprintf(stderr, "Error opening files : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char key[ALPHABET_SIZE + 1]; // +1 for null terminator
    if (mode == 's') {
        generate_substitution_key(key, DEFAULT_SEED);
    }

    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (mode == 'c') {
            fputc(caesar_cipher(ch, shift), output);
        } else if (mode == 's') {
            fputc(substitution_cipher(ch, key, shift < 0), output);
        }
    }

    fclose(input);
    fclose(output);
}

// Encrypt File using Rail Fence Cipher
void rail_fence_encrypt_file(const char* input_path, const char* output_path, int rails) {
    FILE* input = fopen(input_path, "r");
    if (!input) {
        fprintf(stderr, "Error opening input file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen(output_path, "w");
    if (!output) {
        fclose(input);
        fprintf(stderr, "Error opening output file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)) {
        char* encrypted = rail_fence_encrypt(buffer, rails);
        fprintf(output, "%s", encrypted);
        free(encrypted);
    }

    fclose(input);
    fclose(output);
}

// Decrypt File using Rail Fence Cipher
void rail_fence_decrypt_file(const char* input_path, const char* output_path, int rails) {
    FILE* input = fopen(input_path, "r");
    if (!input) {
        fprintf(stderr, "Error opening input file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen(output_path, "w");
    if (!output) {
        fclose(input);
        fprintf(stderr, "Error opening output file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)) {
        char* decrypted = rail_fence_decrypt(buffer, rails);
        fprintf(output, "%s", decrypted);
        free(decrypted);
    }

    fclose(input);
    fclose(output);
}

// Write Data to File
void write_to_file(const char* file) {
}

/*
FUNCTION process_file(string input_path, string output_path, integer shift)
    OPEN file input at input_path for reading
    OPEN file output at output_path for writing
    IF either input or output could not be opened THEN
        PRINT error message
        EXIT program
    ENDIF

    WHILE there are more characters to read from input
        READ character from input
        ENCRYPT character using cipher function with given shift
        WRITE encrypted character to output
    END WHILE

    CLOSE input file
    CLOSE output file
END FUNCTION
*/
