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


