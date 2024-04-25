#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Welcome to File Cipher Program\n");

        char mode, choice;
        int shift;
        char input_file[100];
        char output_file[100];

        do {
            printf("\nEnter mode ('c' for Caesar, 's' for Substitution): ");
            scanf(" %c", &mode);
            if (strchr("csCS", mode) == NULL) {
                printf("Invalid mode.\n");
                continue;
            }

            printf("Enter shift: ");
            scanf("%d", &shift);

            printf("Choose operation (e for encryption, d for decryption): ");
            scanf(" %c", &choice);
            if (strchr("edED", choice) == NULL) {
                printf("Invalid operation choice.\n");
                continue;
            }
            shift = (choice == 'd' || choice == 'D') ? -abs(shift) : abs(shift);

            printf("Enter input file name: ");
            scanf("%s", input_file);

            printf("Enter output file name: ");
            scanf("%s", output_file);

            process_file(input_file, output_file, shift, mode);

            printf("\nFile has been processed successfully.\n");
            printf("Do you want to continue? (y/n): ");
            scanf(" %c", &choice);
        } while (choice == 'y' || choice == 'Y');
    } else if (argc == 6) {
        char mode = argv[1][0];
        int shift = atoi(argv[2]);
        char* input_file = argv[3];
        char* output_file = argv[4];
        char operation = argv[5][0];

        process_file(input_file, output_file, shift, mode);

        printf("File has been processed successfully.\n");
    } else {
        fprintf(stderr, "Usage: %s <mode> <shift> <input file> <output file> <operation>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/*
START PROGRAM with arguments: mode, shift, input_file, output_file
    IF number of arguments is not exactly 5 THEN
        PRINT usage message
        EXIT program
    ENDIF
    
    SET mode based on argument (encrypt or decrypt)
    SET shift as integer from argument
    IF mode is 'decrypt' THEN
        SET shift to -shift
    ENDIF
    
    CALL function process_file with arguments input_file, output_file, and shift
    PRINT confirmation message that file processing was successful
END PROGRAM
*/
