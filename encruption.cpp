#include <stdio.h>

int main() {
    char text[100];
    int i, k;

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the key (1-25): ");
    scanf("%d", &k);

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = 'a' + (text[i] - 'a' + k) % 26;
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = 'A' + (text[i] - 'A' + k) % 26;
        }
    }

    printf("Encrypted text: %s\n", text);

    return 0;
}

