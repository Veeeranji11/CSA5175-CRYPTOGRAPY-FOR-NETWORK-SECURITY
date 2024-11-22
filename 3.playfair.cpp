#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
char matrix[SIZE][SIZE];

// Construct Playfair matrix from keyword
void constructMatrix(char *key) {
    int used[26] = {0}; // Track used letters
    int row = 0, col = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;
            if (col == SIZE) { col = 0; row++; }
        }
    }
    // Fill the remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip 'J'
        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            if (col == SIZE) { col = 0; row++; }
        }
    }
}

// Find position of a letter in the matrix
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (matrix[i][j] == ch) { *row = i; *col = j; return; }
}

// Encrypt the text using Playfair rules
void encrypt(char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int k = 0;
    for (int i = 0; i < len; i += 2) {
        char a = toupper(plaintext[i]);
        char b = (i + 1 < len) ? toupper(plaintext[i + 1]) : 'X';
        if (a == 'J') a = 'I'; if (b == 'J') b = 'I';
        if (a == b) b = 'X'; // Same letter: add 'X'

        int row1, col1, row2, col2;
        findPosition(a, &row1, &col1);
        findPosition(b, &row2, &col2);

        if (row1 == row2) { ciphertext[k++] = matrix[row1][(col1 + 1) % SIZE]; ciphertext[k++] = matrix[row2][(col2 + 1) % SIZE]; }
        else if (col1 == col2) { ciphertext[k++] = matrix[(row1 + 1) % SIZE][col1]; ciphertext[k++] = matrix[(row2 + 1) % SIZE][col2]; }
        else { ciphertext[k++] = matrix[row1][col2]; ciphertext[k++] = matrix[row2][col1]; }
    }
    ciphertext[k] = '\0';
}

int main() {
    char key[50], plaintext[100], ciphertext[100];
    printf("Enter keyword: ");
    scanf("%s", key);
    constructMatrix(key);

    printf("Enter plaintext: ");
    scanf("%s", plaintext);

    encrypt(plaintext, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}

