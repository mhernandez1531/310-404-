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

