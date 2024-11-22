#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char cipherSquare[SIZE][SIZE];

// Function to remove duplicates from a keyword
void createCipherSquare(const char *keyword) {
    int used[26] = {0};
    int index = 0;

    // Fill the cipher square with the keyword
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (ch == 'J') ch = 'I'; // Combine I and J
        if (!used[ch - 'A']) {
            cipherSquare[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }

    // Fill in the remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip J
        if (!used[ch - 'A']) {
            cipherSquare[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
}

// Function to find the position of a letter in the cipher square
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat J as I
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cipherSquare[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decrypt a pair of letters
void decryptPair(char *a, char *b) {
    int row1, col1, row2, col2;
    findPosition(*a, &row1, &col1);
    findPosition(*b, &row2, &col2);

    if (row1 == row2) {
        // Same row: Move left
        *a = cipherSquare[row1][(col1 + SIZE - 1) % SIZE];
        *b = cipherSquare[row2][(col2 + SIZE - 1) % SIZE];
    } else if (col1 == col2) {
        // Same column: Move up
        *a = cipherSquare[(row1 + SIZE - 1) % SIZE][col1];
        *b = cipherSquare[(row2 + SIZE - 1) % SIZE][col2];
    } else {
        // Rectangle swap columns
        *a = cipherSquare[row1][col2];
        *b = cipherSquare[row2][col1];
    }
}

// Function to decrypt the ciphertext
void decryptMessage(const char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];
        decryptPair(&a, &b);
        plaintext[i] = a;
        plaintext[i + 1] = b;
    }
    plaintext[len] = '\0';
}

int main() {
    const char keyword[] = "PLAYFAIR";
    const char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONECUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[200];

    // Create cipher square
    createCipherSquare(keyword);

    // Print cipher square
    printf("Cipher Square:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", cipherSquare[i][j]);
        }
        printf("\n");
    }

    // Decrypt the message
    decryptMessage(ciphertext, plaintext);

    // Print the plaintext
    printf("\nCiphertext: %s\n", ciphertext);
    printf("Decrypted Message: %s\n", plaintext);

    return 0;
}

