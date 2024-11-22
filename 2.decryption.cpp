#include <stdio.h>
#include <string.h>

void encrypt(char *text, char *cipher_alphabet) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = cipher_alphabet[text[i] - 'a'];
        }
    }
}

void decrypt(char *text, char *cipher_alphabet) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            for (int j = 0; j < 26; j++) {
                if (text[i] == cipher_alphabet[j]) {
                    text[i] = 'a' + j;
                    break;
                }
            }
        }
    }
}

int main() {
    char text[100], cipher_alphabet[27];

    printf("Enter the text (lowercase letters only): ");
    scanf("%s", text);

    printf("Enter the cipher alphabet (26 unique letters): ");
    scanf("%s", cipher_alphabet);

    encrypt(text, cipher_alphabet);
    printf("Encrypted text: %s\n", text);

    decrypt(text, cipher_alphabet);
    printf("Decrypted text: %s\n", text);

    return 0;
}

