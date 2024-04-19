#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(int argc, char *argv[]){
	if(argc < 5) {
		fprintf(stderr, "usage: %s <mode> <shift> <input file> <output file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char mode = argv[1][0]; //'c' for caesar, 's' for substitution
	int decrypt = strcmp(argv[2], "decrypt") == 0;
	int shift = atoi(argv[3]);
	if(decrypt) {
		shift = -shift; //use negative shift for decryption 
	} 

	process_file(argv[3], argv[5], shift, mode);
	
	printf("File has been processed successfully.\n");
	return EXIT_SUCCESS;
};


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
