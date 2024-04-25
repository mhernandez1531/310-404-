#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define ALPHABET_SIZE 26
#define DEFAULT_SEED "some_seed_string"

char* rail_fence_encrypt(const char* message, int rails) {
   int len = strlen(message);
    char* encrypted = (char*)malloc(len + 1);
    if (!encrypted) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
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
    encrypted[k] = '\0';
    return encrypted;
}
    return NULL; // Placeholder return
}

char* rail_fence_decrypt(const char* message, int rails) {
    int len = strlen(message);
    char* decrypted = (char*)malloc(len + 1);
    if (!decrypted) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
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
    decrypted[len] = '\0';
    return decrypted;
}
    return NULL; // Placeholder return
}

char caesar_cipher(char ch, int shift){
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';  // Simpler base determination
        return (char)(((ch - base + shift) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE + base);  // Simplified modulo operation
    }
    return ch;
}

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

void prompt_user_input() {
    char input_path[256]; // Assuming maximum path length of 255 characters
    char output_path[256];
    int shift;
    char mode;

    // Loop for reading input path until a valid one is provided
    do {
        printf("Enter input file path: ");
        scanf("%s", input_path);
    } while (access(input_path, F_OK) == -1);

    // Loop for reading output path until a valid one is provided
    do {
        printf("Enter output file path: ");
        scanf("%s", output_path);
    } while (access(output_path, F_OK) != -1);

    // Loop for reading shift until a valid one is provided
    do {
        printf("Enter shift value (-25 to 25): ");
        scanf("%d", &shift);
    } while (shift < -25 || shift > 25);

    // Loop for reading mode until a valid one is provided
    do {
        printf("Enter mode (c for Caesar cipher, s for substitution cipher): ");
        scanf(" %c", &mode);
    } while (mode != 'c' && mode != 's');

    process_file(input_path, output_path, shift, mode);
}

	

/*
FUNCTION cipher(character ch, integer shift)
    IF ch is a letter THEN
        IF ch is lowercase THEN
            base <- 'a'
        ELSE
            base <- 'A'
        ENDIF
        RETURN shifted character by 'shift' positions within alphabet bounds
    ELSE
        RETURN ch
    ENDIF
END FUNCTION

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
