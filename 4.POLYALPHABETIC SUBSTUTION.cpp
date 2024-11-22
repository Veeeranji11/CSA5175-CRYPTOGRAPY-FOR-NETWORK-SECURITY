#include <stdio.h>
#include <string.h>
#include <ctype.h>

void polyalphabeticEncrypt(char *plaintext, char *key, char *ciphertext) {
    int i, j = 0;
    int keyLength = strlen(key);

    for(i = 0; i < strlen(plaintext); i++) {
        if(isalpha(plaintext[i])) {
            ciphertext[i] = ((toupper(plaintext[i]) - 'A') + (toupper(key[j % keyLength]) - 'A')) % 26 + 'A';
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[100], key[100], ciphertext[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    polyalphabeticEncrypt(plaintext, key, ciphertext);

    printf("Encrypted Text: %s\n", ciphertext);
    return 0;
}

