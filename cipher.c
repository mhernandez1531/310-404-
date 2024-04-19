#include "cipher.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h>

char caesar_cipher(char ch, int shift){
	if(isalpha(ch)){
		char base = 'A' + (islower(ch) ? 32 : 0); //determine if a letter uppercase or lowercase 
		return(char)(((ch - base + shift) % 26 + 26) % 26 + base); //apply cihper and handle negative shifts 
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
	char standard_alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	strcpy(key, standard_alphabet);
	int seed_length = strlen(seed);
	for(int i = 0; i <26; i++){
		int j = (seed[i % seed_length] + i) % 26;
		char temp = key[i];
		key[i] = key[j];
		key[j] = temp;
	}
}


void process_file(const char *input_path, const char *output_path, int shift, char mode){
	FILE *input = fopen(input_path, "r");
	FILE *output = fopen(output_path, "w");

	if(!input || !output){
		fprintf(stderr, "Error opening files : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	char mode = 'c';
	char key[27], ch;
	if(mode =='s'){
		generate_substitution_key(key, "some_seed_string");
	}	
 
	while((ch = fgetc(input)) != EOF){
		if(mode == 'c'){
			fputc(caesar_cipher(ch, shift), output);// encrypt/decrypt the character and write output 
		} else if (mode == 's'){
			fputc(substitution_cipher(ch, key, shift < 0), output);
		}
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
