#include <stdio.h>

#include <stdlib.h>

#include <string.h>



// Initial Permutation Table

int IP[] = {

    58, 50, 42, 34, 26, 18, 10, 2,

    60, 52, 44, 36, 28, 20, 12, 4,

    62, 54, 46, 38, 30, 22, 14, 6,

    64, 56, 48, 40, 32, 24, 16, 8,

    57, 49, 41, 33, 25, 17, 9, 1,

    59, 51, 43, 35, 27, 19, 11, 3,

    61, 53, 45, 37, 29, 21, 13, 5,

    63, 55, 47, 39, 31, 23, 15, 7

};



// Final Permutation Table

int FP[] = {

    40, 8, 48, 16, 56, 24, 64, 32,

    39, 7, 47, 15, 55, 23, 63, 31,

    38, 6, 46, 14, 54, 22, 62, 30,

    37, 5, 45, 13, 53, 21, 61, 29,

    36, 4, 44, 12, 52, 20, 60, 28,

    35, 3, 43, 11, 51, 19, 59, 27,

    34, 2, 42, 10, 50, 18, 58, 26,

    33, 1, 41, 9, 49, 17, 57, 25

};



// Permuted Choice 1 (PC1) Table

int PC1[] = {

    57, 49, 41, 33, 25, 17, 9,

    1, 58, 50, 42, 34, 26, 18,

    10, 2, 59, 51, 43, 35, 27,

    19, 11, 3, 60, 52, 44, 36,

    63, 55, 47, 39, 31, 23, 15,

    7, 62, 54, 46, 38, 30, 22,

    14, 6, 61, 53, 45, 37, 29,

    21, 13, 5, 28, 20, 12, 4

};



// Permuted Choice 2 (PC2) Table

int PC2[] = {

    14, 17, 11, 24, 1, 5,

    3, 28, 15, 6, 21, 10,

    23, 19, 12, 4, 26, 8,

    16, 7, 27, 20, 13, 2,

    41, 52, 31, 37, 47, 55,

    30, 40, 51, 45, 33, 48,

    44, 49, 39, 56, 34, 53,

    46, 42, 50, 36, 29, 32

};



// Expansion Table

int E[] = {

    32, 1, 2, 3, 4, 5,

    4, 5, 6, 7, 8, 9,

    8, 9, 10, 11, 12, 13,

    12, 13, 14, 15, 16, 17,

    16, 17, 18, 19, 20, 21,

    20, 21, 22, 23, 24, 25,

    24, 25, 26, 27, 28, 29,

    28, 29, 30, 31, 32, 1

};



// S-boxes Table

int S[8][4][16] = {

    { // S1

        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},

        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},

        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},

        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}

    },

    { // S2

        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},

        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},

        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},

        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}

    },

    { // S3

        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},

        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},

        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},

        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}

    },

    { // S4

        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},

        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},

        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},

        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}

    },

    { // S5

        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},

        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},

        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},

        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}

    },

    { // S6

        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},

        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},

        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},

        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}

    },

    { // S7

        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},

        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},

        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},

        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}

    },

    { // S8

        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},

        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},

        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},

        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}

    }

};



// Permutation Table

int P[] = {

    16, 7, 20, 21, 29, 12, 28, 17,

    1, 15, 23, 26, 5, 18, 31, 10,

    2, 8, 24, 14, 32, 27, 3, 9,

    19, 13, 30, 6, 22, 11, 4, 25

};



// Left Shifts for each round

int left_shifts[] = {

    1, 1, 2, 2, 2, 2, 2, 2,

    1, 2, 2, 2, 2, 2, 2, 1

};



// Function to apply a permutation table on input

void permute(unsigned char *output, unsigned char *input, int *table, int n) {

    for (int i = 0; i < n; i++) {

        int bit = table[i] - 1;

        int byte = bit / 8;

        int bit_in_byte = bit % 8;

        int value = (input[byte] >> (7 - bit_in_byte)) & 1;

        output[i / 8] |= value << (7 - (i % 8));

    }

}

void left_circular_shift(unsigned char *input, int n, int shift) {

    unsigned char tmp[4];

    memcpy(tmp, input, 4);

    int shift_bytes = shift / 8;

    int shift_bits = shift % 8;

    for (int i = 0; i < 4; i++) {

        int src_byte = (i + shift_bytes) % 4;

        int src_byte_next = (src_byte + 1) % 4;

        input[i] = (tmp[src_byte] << shift_bits) | (tmp[src_byte_next] >> (8 - shift_bits));

    }

}

void generate_keys(unsigned char *key, unsigned char subkeys[16][6]) {

    unsigned char permuted_key[7] = {0};

    permute(permuted_key, key, PC1, 56);

    unsigned char C[4] = {0};

    unsigned char D[4] = {0};

    memcpy(C, permuted_key, 3);

    C[3] = permuted_key[3] & 0xF0;

    memcpy(D, permuted_key + 3, 4);

    D[0] = (D[0] << 4) | (D[1] >> 4);

    D[1] = (D[1] << 4) | (D[2] >> 4);

    D[2] = (D[2] << 4) | (D[3] >> 4);

    D[3] = (D[3] << 4);

    for (int i = 0; i < 16; i++) {

        left_circular_shift(C, 28, left_shifts[i]);

        left_circular_shift(D, 28, left_shifts[i]);

        unsigned char CD[7] = {0};

        memcpy(CD, C, 3);

        CD[3] = (C[3] & 0xF0) | (D[0] >> 4);

        memcpy(CD + 4, D, 3);



        permute(subkeys[i], CD, PC2, 48);

    }

}

void f(unsigned char *output, unsigned char *input, unsigned char *subkey) {

    unsigned char expanded[6] = {0};

    permute(expanded, input, E, 48);



    for (int i = 0; i < 6; i++) {

        expanded[i] ^= subkey[i];

    }

    unsigned char substituted[4] = {0};

    for (int i = 0; i < 8; i++) {

        int row = ((expanded[i / 2] >> (7 - 4 * (i % 2))) & 2) | ((expanded[i / 2] >> (3 - 4 * (i % 2))) & 1);

        int col = (expanded[i / 2] >> (4 * (i % 2) + 1)) & 0xF;

        int s_value = S[i][row][col];

        substituted[i / 2] |= s_value << (4 * (1 - (i % 2)));

    }



    permute(output, substituted, P, 32);

}

void des_decrypt(unsigned char *ciphertext, unsigned char *plaintext, unsigned char subkeys[16][6]) {

    unsigned char permuted_text[8] = {0};

    permute(permuted_text, ciphertext, IP, 64);

    unsigned char L[4] = {0};

    unsigned char R[4] = {0};

    memcpy(L, permuted_text, 4);

    memcpy(R, permuted_text + 4, 4);

    for (int i = 15; i >= 0; i--) {

        unsigned char previous_R[4] = {0};

        memcpy(previous_R, R, 4);

        unsigned char f_output[4] = {0};

        f(f_output, R, subkeys[i]);

        for (int j = 0; j < 4; j++) {

            R[j] = L[j] ^ f_output[j];

            L[j] = previous_R[j];

        }

    }

    unsigned char preoutput[8] = {0};

    memcpy(preoutput, R, 4);

    memcpy(preoutput + 4, L, 4);

    permute(plaintext, preoutput, FP, 64);

}

int main() {

    unsigned char key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};  // Example key

    unsigned char ciphertext[8] = {0x85, 0xE8, 0x13, 0x54, 0x0F, 0x0A, 0xB4, 0x05};  // Example ciphertext

    unsigned char plaintext[8] = {0};

    unsigned char subkeys[16][6] = {0};

    generate_keys(key, subkeys);

    unsigned char reversed_subkeys[16][6] = {0};

    for (int i = 0; i < 16; i++) {

        memcpy(reversed_subkeys[i], subkeys[15 - i], 6);

    }

    des_decrypt(ciphertext, plaintext, reversed_subkeys);

    printf("Decrypted text: ");

    for (int i = 0; i < 8; i++) {

        printf("%02X ", plaintext[i]);

    }

    printf("\n");

    return 0;

}

