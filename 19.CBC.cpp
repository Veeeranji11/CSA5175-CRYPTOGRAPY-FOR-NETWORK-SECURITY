#include <stdio.h>
#include <string.h>

int main() {
    unsigned char key[24] = "123456789012345678901234"; // 3DES key (24 bytes)
    unsigned char iv[8] = "12345678";                  // Initialization vector
    unsigned char plaintext[] = "Test message.";      // Plaintext to encrypt
    unsigned char ciphertext[64];                     // Buffer for ciphertext

    DES_cblock key1, key2, key3, ivec;
    DES_key_schedule ks1, ks2, ks3;

    // Split key into three DES keys and copy IV
    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);
    memcpy(ivec, iv, 8);

    // Set up key schedules
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    // Perform 3DES encryption in CBC mode
    DES_ede3_cbc_encrypt(plaintext, ciphertext, strlen((char *)plaintext) + 1, &ks1, &ks2, &ks3, &ivec, DES_ENCRYPT);

    // Print ciphertext in hex
    printf("Ciphertext: ");
    for (int i = 0; i < strlen((char *)plaintext) + 1; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

