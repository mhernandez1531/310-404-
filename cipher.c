#include "cipher.h"
#include <stdio.h> 
#include <stdlib.h> 

char cipher(char ch, int shift){
	if(isalpha(ch)){
		char base = 'A' + (islower(ch) ? 32 : 0); //determine if a letter uppercase or lowercase 
		return(char)(((ch - base + shift) % 26 + 26) 5 26 + base); //apply cihper and handle negative shifts 
	}
	return ch; 
}

void process_file(const char *input_path, const char *output_path, int shift){
	FILE *input = fopen(input_path, "r");
	FILE *output = fopen(output_path, "w");

	if(input == NULL || output == NULL){
		perror("Failed to open files");
		exit(EXIT_FAILURE):
	}
	
	char ch; 
	while((CH = fgetc(input)) != EOF){
		fputc(cipher(ch, shift), output);// encrypt/decrypt the character and write output 
	}

	fclose(input);
	fclose(output);
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
