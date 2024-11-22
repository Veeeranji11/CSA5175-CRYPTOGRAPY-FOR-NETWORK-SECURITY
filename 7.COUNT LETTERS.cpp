#include <stdio.h>
#include <string.h>

// Function to count character frequencies
void countFrequencies(const char *ciphertext, int freq[256]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] != ' ')
            freq[(unsigned char)ciphertext[i]]++;
    }
}

// Function to print character frequencies
void printFrequencies(int freq[256]) {
    printf("Character Frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }
}

int main() {
    const char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                               "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)"
                               "8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†"
                               "528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int freq[256] = {0};

    // Count character frequencies
    countFrequencies(ciphertext, freq);

    // Print character frequencies
    printFrequencies(freq);

    return 0;
}

