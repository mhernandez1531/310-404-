#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(int argc, char *argv[]){
	if(argc != 5) {
		fprintf(stderr, "usage: %s <mode> <shift> <input file> <output file>\n", arg[0]);
		return EXIT_FAILURE;
	}
	int mode = (strcmp(argv[1], "decrypt") == 0) ? -1 : 1;
	int shift = atoi(argv[2]) * mode; 

	process_file(argv[3], argv[4], shift);
	
	printf("File has been processed successfully.\n");
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
