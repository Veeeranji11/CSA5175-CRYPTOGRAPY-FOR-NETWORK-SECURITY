#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2  // For a 2x2 matrix

// Function to convert a letter to its corresponding number (A=0, B=1, ..., Z=25)
int letterToNum(char letter) {
    return toupper(letter) - 'A';
}

// Function to convert a number back to a letter (0=A, 1=B, ..., 25=Z)
char numToLetter(int num) {
    return num + 'A';
}

// Function to perform matrix multiplication (mod 26) for encryption
void matrixMultiply(int key[SIZE][SIZE], int input[SIZE], int output[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        output[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            output[i] = (output[i] + key[i][j] * input[j]) % 26;
        }
    }
}

// Function to find the modular inverse of a matrix (mod 26) for decryption
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // This should never happen if the matrix is invertible
}

// Function to find the inverse of the matrix (mod 26)
int matrixInverse(int key[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (determinant < 0) determinant += 26;

    int invDet = modInverse(determinant, 26);
    if (invDet == -1) return -1;  // Inverse doesn't exist

    inverse[0][0] = invDet * key[1][1] % 26;
    inverse[0][1] = -invDet * key[0][1] % 26;
    inverse[1][0] = -invDet * key[1][0] % 26;
    inverse[1][1] = invDet * key[0][0] % 26;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (inverse[i][j] < 0) inverse[i][j] += 26;

    return 0;
}

// Function to encrypt the plaintext using Hill Cipher
void hillEncrypt(char* plaintext, int key[SIZE][SIZE], char* ciphertext) {
    int len = strlen(plaintext);
    int input[SIZE], output[SIZE];
    int idx = 0;

    // Encrypt each pair of letters
    for (int i = 0; i < len; i += SIZE) {
        // Get next pair of letters (convert to numbers)
        input[0] = letterToNum(plaintext[i]);
        input[1] = letterToNum(plaintext[i + 1]);

        // Perform matrix multiplication and store in output
        matrixMultiply(key, input, output);

        // Convert back to letters
        ciphertext[idx++] = numToLetter(output[0]);
        ciphertext[idx++] = numToLetter(output[1]);
    }
    ciphertext[idx] = '\0';  // Null terminate the ciphertext string
}

// Function to decrypt the ciphertext using Hill Cipher
void hillDecrypt(char* ciphertext, int key[SIZE][SIZE], char* decryptedText) {
    int inverse[SIZE][SIZE];
    int len = strlen(ciphertext);
    int input[SIZE], output[SIZE];
    int idx = 0;

    // Find the inverse of the key matrix
    if (matrixInverse(key, inverse) == -1) {
        printf("Matrix is not invertible!\n");
        return;
    }

    // Decrypt each pair of letters
    for (int i = 0; i < len; i += SIZE) {
        // Get next pair of letters (convert to numbers)
        input[0] = letterToNum(ciphertext[i]);
        input[1] = letterToNum(ciphertext[i + 1]);

        // Perform matrix multiplication with the inverse key matrix
        matrixMultiply(inverse, input, output);

        // Convert back to letters
        decryptedText[idx++] = numToLetter(output[0]);
        decryptedText[idx++] = numToLetter(output[1]);
    }
    decryptedText[idx] = '\0';  // Null terminate the decrypted text
}

int main() {
    // Key matrix for Hill Cipher
    int key[SIZE][SIZE] = {{9, 4}, {5, 7}};

    // Input plaintext message
    char plaintext[] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    char ciphertext[100], decryptedText[100];

    // Encrypt the plaintext
    hillEncrypt(plaintext, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    // Decrypt the ciphertext
    hillDecrypt(ciphertext, key, decryptedText);
    printf("Decrypted message: %s\n", decryptedText);

    return 0;
}

