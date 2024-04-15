#include <gtest/gtest.h>

#include "cipher_tests.hh"


TEST(CipherTests, CaesarCipherEncryptDecrypt) {
    const char* test_string = "Hello, World!";
    int shift = 3;

    // Test encryption
    char* encrypted = caesar_cipher_string(test_string, shift);
    EXPECT_STREQ(encrypted, "Khoor, Zruog!");

    // Test decryption
    char* decrypted = caesar_cipher_string(encrypted, -shift);
    EXPECT_STREQ(decrypted, test_string);

    // Clean up memory
    free(encrypted);
    free(decrypted);
}
