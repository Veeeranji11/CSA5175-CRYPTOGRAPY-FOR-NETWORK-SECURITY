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

// Function to perform matrix multiplication (mod 26)
void matrixMultiply(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % 26;
            }
        }
    }
}

// Function to calculate the modular inverse of a number (mod 26)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // This should never happen if the matrix is invertible
}

// Function to calculate the inverse of a matrix (mod 26)
int matrixInverse(int matrix[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    if (det < 0) det += 26;
    
    int invDet = modInverse(det, 26);
    if (invDet == -1) return -1;  // Inverse does not exist

    inverse[0][0] = (invDet * matrix[1][1]) % 26;
    inverse[0][1] = (-invDet * matrix[0][1]) % 26;
    inverse[1][0] = (-invDet * matrix[1][0]) % 26;
    inverse[1][1] = (invDet * matrix[0][0]) % 26;

    // Ensure all elements are positive mod 26
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (inverse[i][j] < 0) inverse[i][j] += 26;
        }
    }
    return 0;
}

// Function to decrypt using the inverse of the key matrix
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
        input[0] = letterToNum(ciphertext[i]);
        input[1] = letterToNum(ciphertext[i + 1]);

        // Perform matrix multiplication with the inverse key matrix
        for (int i = 0; i < SIZE; i++) {
            output[i] = 0;
            for (int j = 0; j < SIZE; j++) {
                output[i] = (output[i] + inverse[i][j] * input[j]) % 26;
            }
        }

        // Convert back to letters
        decryptedText[idx++] = numToLetter(output[0]);
        decryptedText[idx++] = numToLetter(output[1]);
    }
    decryptedText[idx] = '\0';
}

// Function to solve the Hill cipher using known plaintext
void solveHillCipher(char* plaintext, char* ciphertext, int key[SIZE][SIZE]) {
    int P[SIZE][SIZE], C[SIZE][SIZE], K[SIZE][SIZE];
    
    // Convert the plaintext and ciphertext to numbers
    for (int i = 0; i < SIZE; i++) {
        P[i][0] = letterToNum(plaintext[i * 2]);
        P[i][1] = letterToNum(plaintext[i * 2 + 1]);
        C[i][0] = letterToNum(ciphertext[i * 2]);
        C[i][1] = letterToNum(ciphertext[i * 2 + 1]);
    }

    // Find the inverse of the plaintext matrix P
    int P_inv[SIZE][SIZE];
    if (matrixInverse(P, P_inv) == -1) {
        printf("Plaintext matrix is not invertible!\n");
        return;
    }

    // Multiply the inverse of P by C to find the key matrix K
    matrixMultiply(P_inv, C, K);

    // Print the key matrix K
    printf("Recovered key matrix K:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", K[i][j]);
        }
        printf("\n");
    }

    // Decrypt the ciphertext using the recovered key matrix
    char decryptedText[100];
    hillDecrypt(ciphertext, K, decryptedText);
    printf("Decrypted message: %s\n", decryptedText);
}

int main() {
    // Known plaintext and corresponding ciphertext
    char plaintext[] = "ME";  // First two letters of plaintext
    char ciphertext[] = "BP";  // Corresponding ciphertext

    // Key matrix (unknown)
    int key[SIZE][SIZE];

    // Perform known plaintext attack to recover the key
    solveHillCipher(plaintext, ciphertext, key);

    return 0;
}

