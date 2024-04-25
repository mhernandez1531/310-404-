#include <gtest/gtest.h>
#include "cipher.hh"

// Test Caesar Cipher Encryption and Decryption
TEST(CipherTests, CaesarCipherEncryptDecrypt) {
    const char* test_string = "Hello, World!";
    int shift = 3;

    // Test encryption
    char* encrypted = caesar_cipher(test_string, shift);
    EXPECT_STREQ(encrypted, "Khoor, Zruog!");

    // Test decryption
    char* decrypted = caesar_cipher(encrypted, -shift);
    EXPECT_STREQ(decrypted, test_string);

    // Clean up memory
    free(encrypted);
    free(decrypted);
}

// Test Substitution Cipher Encryption and Decryption
TEST(CipherTests, SubstitutionCipherEncryptDecrypt) {
    const char* test_string = "Hello, World!";
    const char* key = "QWERTYUIOPASDFGHJKLZXCVBNM";

    // Test encryption
    char* encrypted = substitution_cipher(test_string, key, 0);
    EXPECT_STREQ(encrypted, "Qvrru, Fxrut!");

    // Test decryption
    char* decrypted = substitution_cipher(encrypted, key, 1);
    EXPECT_STREQ(decrypted, test_string);

    // Clean up memory
    free(encrypted);
    free(decrypted);
}

// Test Rail Fence Cipher Encryption and Decryption
TEST(CipherTests, RailFenceCipherEncryptDecrypt) {
    const char* test_string = "Hello, World!";
    int rails = 3;

    // Test encryption
    char* encrypted = rail_fence_encrypt(test_string, rails);
    EXPECT_STREQ(encrypted, "Horel,Wl lo!");

    // Test decryption
    char* decrypted = rail_fence_decrypt(encrypted, rails);
    EXPECT_STREQ(decrypted, test_string);

    // Clean up memory
    free(encrypted);
    free(decrypted);
}
