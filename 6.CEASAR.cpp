#include <stdio.h>
#include <ctype.h>

// Function to find modular inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Decryption function
char affineDecrypt(char c, int a, int b, int a_inv) {
    if (isalpha(c)) {
        c = toupper(c) - 'A'; // Convert to 0-25
        return (char)(((a_inv * (c - b + 26)) % 26) + 'A');
    }
    return c; // Non-alphabetic characters are unchanged
}

int main() {
    // Given ciphertext and derived keys
    char ciphertext[] = "BU..."; // Replace with the actual ciphertext
    int a = 19, b = 25;          // Determined keys
    int a_inv = modInverse(a, 26);

    if (a_inv == -1) {
        printf("Decryption not possible (a has no modular inverse).\n");
        return 1;
    }

    // Decrypt the ciphertext
    char decryptedText[100];
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedText[i] = affineDecrypt(ciphertext[i], a, b, a_inv);
    }
    decryptedText[sizeof(ciphertext) - 1] = '\0';

    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

