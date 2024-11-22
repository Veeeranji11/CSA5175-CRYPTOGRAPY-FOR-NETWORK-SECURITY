#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to generate the cipher sequence from the keyword
void generateCipherSequence(const char *keyword, char cipher[ALPHABET_SIZE]) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;

    // Add the keyword to the cipher sequence
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    // Add the remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
}

// Function to encrypt plaintext using the cipher sequence
void encrypt(const char *plaintext, const char cipher[ALPHABET_SIZE], char *encrypted) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            encrypted[i] = cipher[ch - 'A'];
        } else {
            encrypted[i] = plaintext[i]; // Preserve non-alphabetic characters
        }
    }
    encrypted[strlen(plaintext)] = '\0';
}

// Function to decrypt ciphertext using the cipher sequence
void decrypt(const char *ciphertext, const char cipher[ALPHABET_SIZE], char *decrypted) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (cipher[j] == ch) {
                    decrypted[i] = 'A' + j;
                    break;
                }
            }
        } else {
            decrypted[i] = ciphertext[i]; // Preserve non-alphabetic characters
        }
    }
    decrypted[strlen(ciphertext)] = '\0';
}

int main() {
    const char keyword[] = "CIPHER";
    char cipher[ALPHABET_SIZE];
    char plaintext[] = "HELLO WORLD";
    char encrypted[100], decrypted[100];

    // Generate cipher sequence
    generateCipherSequence(keyword, cipher);

    printf("Keyword: %s\n", keyword);
    printf("Cipher sequence: ");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", cipher[i]);
    }
    printf("\n");

    // Encrypt the plaintext
    encrypt(plaintext, cipher, encrypted);
    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted: %s\n", encrypted);

    // Decrypt the ciphertext
    decrypt(encrypted, cipher, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}

