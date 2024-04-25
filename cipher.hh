#ifndef CIPHER_HH
#define CIPHER_HH

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Encrypts a message using the Rail Fence Cipher.
 *
 * @param message The message to encrypt.
 * @param rails The number of rails to use in the cipher.
 * @return The encrypted message.
 */
char* rail_fence_encrypt(const char* message, int rails);

/**
 * Decrypts a message encrypted with the Rail Fence Cipher.
 *
 * @param message The message to decrypt.
 * @param rails The number of rails used in the original encryption.
 * @return The decrypted message.
 */
char* rail_fence_decrypt(const char* message, int rails);

#ifdef __cplusplus
}
#endif

#endif /* CIPHER_HH */
