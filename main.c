#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Welcome to File Cipher Program\n");

        char mode;
        int shift;
        char input_file[100];
        char output_file[100];

	do {
        printf("\nEnter mode ('c' for Caesar, 's' for Substitution): ");
        scanf(" %c", &mode);

        printf("Enter shift: ");
        scanf("%d", &shift);

        printf("Enter input file name: ");
        scanf("%s", input_file);

        printf("Enter output file name: ");
        scanf("%s", output_file);

        process_file(input_file, output_file, shift, mode);

        printf("\nFile has been processed successfully.\n");
	printf("Do you want to continue? (y/n): ");
        scanf(" %c", &choice);
      } while (choice == 'y' || choice == 'Y');
    } else if (argc == 5) {
        char mode = argv[1][0]; //'c' for caesar, 's' for substitution
	int shift = atoi(argv[2]);
	char* input_file = argv[3];
	char* output_file = argv[4];

        process_file(input_file, output_file, shift, mode);

        printf("File has been processed successfully.\n");
    } else {
        fprintf(stderr, "usage: %s [<mode> <shift> <input file> <output file>]\n", argv[0]);
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
