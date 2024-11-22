#include <stdio.h>
#include <string.h>

#define NUM_ROUNDS 16
#define KEY_SIZE 64
#define SUBKEY_SIZE 48

// Permutations and shift schedule
int PC1[56] = { /* Permutation table to split 64-bit key into two 28-bit halves */ };
int PC2[48] = { /* Permutation table to generate 48-bit subkey */ };
int SHIFT_SCHEDULE[NUM_ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Circular left shift
void circularLeftShift(int *key, int size, int shifts) {
    int temp[shifts];
    for (int i = 0; i < shifts; i++) temp[i] = key[i];
    for (int i = 0; i < size - shifts; i++) key[i] = key[i + shifts];
    for (int i = 0; i < shifts; i++) key[size - shifts + i] = temp[i];
}

// Key generation function
void generateSubkeys(int initialKey[KEY_SIZE], int subkeys[NUM_ROUNDS][SUBKEY_SIZE]) {
    int C[28], D[28], combined[56];
    int i, round;

    // Apply PC1 to split the key into two 28-bit halves
    for (i = 0; i < 28; i++) {
        C[i] = initialKey[PC1[i]];
        D[i] = initialKey[PC1[i + 28]];
    }

    // Generate 16 subkeys
    for (round = 0; round < NUM_ROUNDS; round++) {
        // Shift C and D
        circularLeftShift(C, 28, SHIFT_SCHEDULE[round]);
        circularLeftShift(D, 28, SHIFT_SCHEDULE[round]);

        // Combine C and D
        for (i = 0; i < 28; i++) combined[i] = C[i];
        for (i = 0; i < 28; i++) combined[i + 28] = D[i];

        // Apply PC2 to generate subkey
        for (i = 0; i < SUBKEY_SIZE; i++) {
            subkeys[round][i] = combined[PC2[i]];
        }
    }
}

int main() {
    int initialKey[KEY_SIZE] = { /* 64-bit key input (as 1s and 0s) */ };
    int subkeys[NUM_ROUNDS][SUBKEY_SIZE];

    // Generate subkeys
    generateSubkeys(initialKey, subkeys);

    // Print subkeys
    for (int round = 0; round < NUM_ROUNDS; round++) {
        printf("Subkey %d: ", round + 1);
        for (int i = 0; i < SUBKEY_SIZE; i++) {
            printf("%d", subkeys[round][i]);
        }
        printf("\n");
    }

    return 0;
}

