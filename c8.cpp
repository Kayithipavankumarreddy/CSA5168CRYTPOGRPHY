#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generate_cipher(const char *keyword, char *cipher) {
    int used[ALPHABET_SIZE] = {0}; // Track used letters
    int index = 0;

    // Add keyword letters to cipher first
    for (int i = 0; keyword[i] != '\0'; i++) {
        char letter = toupper(keyword[i]);
        if (isalpha(letter) && !used[letter - 'A']) {
            used[letter - 'A'] = 1;
            cipher[index++] = letter;
        }
    }

    // Add remaining letters of the alphabet
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (!used[letter - 'A']) {
            cipher[index++] = letter;
        }
    }
    cipher[index] = '\0'; // Null-terminate the cipher string
}

void encrypt(const char *plaintext, const char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char letter = toupper(plaintext[i]);
        if (isalpha(letter)) {
            ciphertext[i] = cipher[letter - 'A'];
        } else {
            ciphertext[i] = plaintext[i]; // Keep non-alphabet characters unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
}

void decrypt(const char *ciphertext, const char *cipher, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char letter = ciphertext[i];
        if (isalpha(letter)) {
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (cipher[j] == toupper(letter)) {
                    plaintext[i] = 'A' + j; // Map back to plaintext
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i]; // Keep non-alphabet characters unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the plaintext
}

int main() {
    char keyword[100];
    char cipher[ALPHABET_SIZE + 1];
    char plaintext[100];
    char ciphertext[100];
    char decryptedtext[100];

    printf("Enter the keyword: ");
    scanf("%s", keyword);

    generate_cipher(keyword, cipher);
    printf("Generated cipher: %s\n", cipher);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext); // Read string with spaces

    encrypt(plaintext, cipher, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, cipher, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
