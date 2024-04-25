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
            printf("\nEnter mode ('c' for Caesar, 's' for Substitution, 'r' for Rail Fence): ");
            scanf(" %c", &mode);
            if (strchr("csrCSR", mode) == NULL) {
                printf("Invalid mode.\n");
                continue;
            }

            if (mode == 'r' || mode == 'R') {
                printf("Enter number of rails: ");
                scanf("%d", &shift);
            } else {
                printf("Enter shift: ");
                scanf("%d", &shift);
            }

            printf("Choose operation (e for encryption, d for decryption): ");
            scanf(" %c", &choice);
            if (strchr("edED", choice) == NULL) {
                printf("Invalid operation choice.\n");
                continue;
            }

            if (choice == 'd' || choice == 'D') {
                if (mode == 'c' || mode == 'C' || mode == 's' || mode == 'S') {
                    shift = -abs(shift);  // Ensure shift is negative for decryption
                }
            } else {
                if (mode == 'c' || mode == 'C' || mode == 's' || mode == 'S') {
                    shift = abs(shift);  // Ensure shift is positive for encryption
                }
            }

            printf("Enter input file name: ");
            scanf("%s", input_file);

            printf("Enter output file name: ");
            scanf("%s", output_file);

            if (mode == 'r' || mode == 'R') {
                if (choice == 'e' || choice == 'E') {
                    rail_fence_encrypt_file(input_file, output_file, shift); // Corrected function call
                } else if (choice == 'd' || choice == 'D') {
                    rail_fence_decrypt_file(input_file, output_file, shift); // Corrected function call
                } else {
                    printf("Invalid choice for Rail Fence cipher operation.\n");
                    continue;
                }
            } else {
                process_file(input_file, output_file, shift, mode);
            }

            printf("\nFile has been processed successfully.\n");
            printf("Do you want to continue? (y/n): ");
            scanf(" %c", &choice);
        } while (choice == 'y' || choice == 'Y');
    } else if (argc == 7) {
        char mode = argv[1][0];
        int shift = atoi(argv[2]);
        char* input_file = argv[3];
        char* output_file = argv[4];
        char operation = argv[5][0];
        int rails = atoi(argv[6]);

        if (mode == 'r' || mode == 'R') {
            if (strcmp(input_file, output_file) == 0) {
                printf("Input and output file names cannot be the same for Rail Fence cipher.\n");
                return EXIT_FAILURE;
            }
            if (strcmp(output_file, input_file) == 0) {
                printf("Input and output file names cannot be the same for Rail Fence cipher.\n");
                return EXIT_FAILURE;
            }

            if (rails < 2) {
                printf("Number of rails should be greater than 1.\n");
                return EXIT_FAILURE;
            }

            if (shift != 0) {
                printf("Shift value should be 0 for Rail Fence cipher.\n");
                return EXIT_FAILURE;
            }

            if (strcmp(argv[5], "e") == 0 || strcmp(argv[5], "E") == 0) {
                rail_fence_encrypt_file(input_file, output_file, rails); // Corrected function call
            } else if (strcmp(argv[5], "d") == 0 || strcmp(argv[5], "D") == 0) {
                rail_fence_decrypt_file(input_file, output_file, rails); // Corrected function call
            } else {
                printf("Invalid choice for Rail Fence cipher operation.\n");
                return EXIT_FAILURE;
            }
        } else {
            process_file(input_file, output_file, shift, mode);
        }

        printf("File has been processed successfully.\n");
    } else {
        fprintf(stderr, "Usage: %s <mode> <shift> <input file> <output file> <operation> <rails>\n", argv[0]);
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
