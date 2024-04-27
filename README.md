# 310-404-

File Encryption and Decryption
This project is a simple command-line application written in C that allows for the encryption and decryption of text files using the Caesar cipher, substitution cipher, and a Transposition Cipher i.e. Rail Fence Cipher.

Features:
  Encryption- Shifts the text in the input file by a specified number of places in the alphabet and writes the encrypted text to an output file.
  Decryption- Reverses the encryption process by shifting the text in the input file back to its original form and writing the decrypted text to an output file.

Supported Ciphers:
Caesar cipher: Shifts letters by a given number of places in the alphabet.
Substitution cipher: Replaces each letter with another letter according to a key.
Rail Fence cipher: Rearranges the letters based on the number of rails specified.

Components:
The application is divided into three main files:
  cipher.h - Header file with declarations for the encryption and decryption functions.
  cipher.c - Contains the implementation of the encryption (cipher) and file processing functions.
  main.c - Handles user input and command-line arguments to control the flow of encryption and decryption processes.
  cipher_tests.cc - tests each cipher works 

Usage:
To compile the program, you need a C compiler like GCC. Navigate to the directory containing the source files and run the following command:
gcc -o file_cipher main.c cipher.c

To encrypt a file, use:
./file_cipher encrypt <shift> <input file> <output file>

To decrypt a file, use:
./file_cipher decrypt <shift> <input file> <output file>
Where <shift> is the number of positions each letter in the text should be shifted by in the alphabet.

Note:
(The Caesar cipher is not suitable for secure encryption as it is easily broken. This project is intended for educational purposes or for encrypting data that does not require strong security measures.)




