
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
void createSubstitutionMap(const char *key, char *substitutionMap) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitutionMap[i] = key[i];
    }
}
void monoalphabeticCipher(char *message, const char *substitutionMap) {
    for (int i = 0; message[i] != '\0'; i++) {
        char c = message[i];
        
        if (isupper(c)) {
            message[i] = substitutionMap[c - 'A'];
        } else if (islower(c)) {
            message[i] = tolower(substitutionMap[c - 'a']);
        }
    }
}

int main() {
    char message[256];
    char key[ALPHABET_SIZE + 1]; 
    char substitutionMap[ALPHABET_SIZE];
    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    printf("Enter the substitution key (26 unique letters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    if (strlen(key) != ALPHABET_SIZE) {
        printf("Key must be exactly 26 unique letters.\n");
        return 1;
    }
    createSubstitutionMap(key, substitutionMap);
    monoalphabeticCipher(message, substitutionMap);
    printf("Encrypted message: %s\n", message);

    return 0;
}
