#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5
void prepareMatrix(const char *key, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int seen[26] = {0}; 
    int row = 0, col = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; 
        if (isalpha(ch) && !seen[ch - 'A']) {
            seen[ch - 'A'] = 1;
            matrix[row][col++] = ch;
            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; 
        if (!seen[ch - 'A']) {
            matrix[row][col++] = ch;
            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }
}


void findPosition(char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}


void preprocessMessage(char *message) {
    int len = strlen(message);
    int index = 0;

   
    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            message[index++] = toupper(message[i]);
        }
    }
    message[index] = '\0';

   
    for (int i = 0; i < index - 1; i++) {
        if (message[i] == message[i + 1]) {
            message[i + 1] = 'X'; 
        }
    }

  
    if (index % 2 != 0) {
        message[index++] = 'X';
        message[index] = '\0';
    }
}


void encryptDigraph(char matrix[MATRIX_SIZE][MATRIX_SIZE], char *digraph, char *encrypted) {
    int row1, col1, row2, col2;
    findPosition(matrix, digraph[0], &row1, &col1);
    findPosition(matrix, digraph[1], &row2, &col2);

    if (row1 == row2) {
        encrypted[0] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
        encrypted[1] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
    } else if (col1 == col2) {
        encrypted[0] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
        encrypted[1] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
    } else {
        encrypted[0] = matrix[row1][col2];
        encrypted[1] = matrix[row2][col1];
    }
}


int main() {
    char key[256], message[256], matrix[MATRIX_SIZE][MATRIX_SIZE], encryptedMessage[512];

   
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    
    prepareMatrix(key, matrix);

    
    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 

    
    preprocessMessage(message);

    
    int len = strlen(message);
    for (int i = 0; i < len; i += 2) {
        char digraph[2] = {message[i], message[i + 1]};
        char encrypted[2];
        encryptDigraph(matrix, digraph, encrypted);
        strncat(encryptedMessage, encrypted, 2);
    }

    
    printf("Encrypted message: %s\n", encryptedMessage);

    return 0;
}
