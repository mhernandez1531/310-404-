// cipher.hh

#ifdef __cplusplus
extern "C" {
#endif

// Other cipher function declarations...

/**
 * Encrypts a message using the Rail Fence Cipher.
 *
 * The message to encrypt.
 * The number of rails to use in the cipher.
 * The encrypted message.
 */
char* rail_fence_encrypt(const char* message, int rails);

/**
 * Decrypts a message encrypted with the Rail Fence Cipher.
 *
 * message The message to decrypt.
 * ails The number of rails used in the original encryption.
 * return The decrypted message.
 */
char* rail_fence_decrypt(const char* message, int rails);

#ifdef __cplusplus
}
#endif
