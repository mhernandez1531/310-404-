#include <gtest/gtest.h>
#include "cipher.hh"

// Test Caesar Cipher Encryption and Decryption
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

// Test Substitution Cipher Encryption and Decryption
TEST(CipherTests, SubstitutionCipherEncryptDecrypt) {
    const char* test_string = "Hello, World!";
    const char* key = "QWERTYUIOPASDFGHJKLZXCVBNM";

    // Test encryption
    char* encrypted = substitution_cipher_encrypt(test_string, key);
    EXPECT_STREQ(encrypted, "Qvrru, Fxrut!");

    // Test decryption
    char* decrypted = substitution_cipher_decrypt(encrypted, key);
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
    char* encrypted = rail_fence_cipher_encrypt(test_string, rails);
    EXPECT_STREQ(encrypted, "Horel,Wl lo!");

    // Test decryption
    char* decrypted = rail_fence_cipher_decrypt(encrypted, rails);
    EXPECT_STREQ(decrypted, test_string);

    // Clean up memory
    free(encrypted);
    free(decrypted);
}
