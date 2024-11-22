#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Playfair matrix
char matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

// Function to find the position of a letter in the Playfair matrix
void findPosition(char letter, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to preprocess the input string by replacing 'J' with 'I' and ensuring even length
void preprocessText(char *text, char *processedText) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == 'J') text[i] = 'I'; // Replace 'J' with 'I'
        if (i < strlen(text) - 1 && text[i] == text[i + 1]) {
            processedText[j++] = text[i];
            processedText[j++] = 'X'; // Add filler 'X' if same letter appears consecutively
            i++;
        } else {
            processedText[j++] = text[i];
        }
    }
    if (j % 2 != 0) {  // If length is odd, add 'X' at the end
        processedText[j++] = 'X';
    }
    processedText[j] = '\0';
}

// Function to encrypt the plaintext using Playfair cipher
void playfairEncrypt(char *text, char *ciphertext) {
    char processedText[100];
    preprocessText(text, processedText);  // Preprocess the text

    int len = strlen(processedText);
    int row1, col1, row2, col2;

    for (int i = 0; i < len; i += 2) {
        findPosition(processedText[i], &row1, &col1);
        findPosition(processedText[i + 1], &row2, &col2);

        // If letters are in the same row, shift columns to the right
        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        }
        // If letters are in the same column, shift rows down
        else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        }
        // If letters form a rectangle, swap columns
        else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char text[100], ciphertext[100];

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;  // Remove newline character

    // Encrypt the text using Playfair cipher
    playfairEncrypt(text, ciphertext);

    printf("Ciphertext: ");
    for (int i = 0; i < strlen(ciphertext); i++) {
        printf("%c", toupper(ciphertext[i]));
    }
    printf("\n");

    return 0;
}

