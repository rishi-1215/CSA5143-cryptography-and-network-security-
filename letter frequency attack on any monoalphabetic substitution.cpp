#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define ALPHABET_SIZE 26

#define MAX_TEXT_SIZE 1000

int compare(const void *a, const void *b) {

    return (*(int *)b - *(int *)a);

}

int main() {

    char ciphertext[MAX_TEXT_SIZE];

    int top_n;

    char english_freq[] = "etaoinshrdlcumwfgypbvkjxqz";

    printf("Enter the ciphertext: ");

    fgets(ciphertext, sizeof(ciphertext), stdin);

    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("Enter the number of top possible plaintexts: ");

    scanf("%d", &top_n);

    int cipher_freq[ALPHABET_SIZE] = {0};

    for (int i = 0; ciphertext[i] != '\0'; i++) {

        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {

            cipher_freq[ciphertext[i] - 'a']++;

        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {

            cipher_freq[ciphertext[i] - 'A']++;

        }

    }

    int indices[ALPHABET_SIZE];

    for (int i = 0; i < ALPHABET_SIZE; i++) {

        indices[i] = i;

    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {

        for (int j = i + 1; j < ALPHABET_SIZE; j++) {

            if (cipher_freq[indices[i]] < cipher_freq[indices[j]]) {

                int temp = indices[i];

                indices[i] = indices[j];

                indices[j] = temp;

            }

        }

    }

    for (int i = 0; i < top_n; i++) {

        char substitution[ALPHABET_SIZE];

        for (int j = 0; j < ALPHABET_SIZE; j++) {

            substitution[indices[j]] = english_freq[(j + i) % ALPHABET_SIZE];

        }

        char plaintext[MAX_TEXT_SIZE];

        int len = strlen(ciphertext);

        for (int j = 0; j < len; j++) {

            if (ciphertext[j] >= 'a' && ciphertext[j] <= 'z') {

                plaintext[j] = substitution[ciphertext[j] - 'a'];

            } else if (ciphertext[j] >= 'A' && ciphertext[j] <= 'Z') {

                plaintext[j] = substitution[ciphertext[j] - 'A'];

            } else {

                plaintext[j] = ciphertext[j];

            }

        }

        plaintext[len] = '\0';

        printf("Plaintext %d: %s\n", i + 1, plaintext);

    }

    return 0;

}

