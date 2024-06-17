#include <stdio.h>
#include <stdint.h>
#include <string.h>
int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1,  58, 50, 42, 34, 26, 18,
    10, 2,  59, 51, 43, 35, 27,
    19, 11, 3,  60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7,  62, 54, 46, 38, 30, 22,
    14, 6,  61, 53, 45, 37, 29,
    21, 13, 5,  28, 20, 12, 4
};
int PC2[] = {
    14, 17, 11, 24, 1,  5,
    3,  28, 15, 6,  21, 10,
    23, 19, 12, 4,  26, 8,
    16, 7,  27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
int SHIFTS[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};
uint32_t left_circular_shift(uint32_t value, int shifts) {
    return ((value << shifts) | (value >> (28 - shifts))) & 0x0FFFFFFF;
}
void generate_subkeys(uint8_t initial_key[8], uint8_t subkeys[16][6]) {
    uint64_t permuted_key = 0;
    for (int i = 0; i < 56; ++i) {
        permuted_key <<= 1;
        permuted_key |= (initial_key[(PC1[i] - 1) / 8] >> (7 - ((PC1[i] - 1) % 8))) & 0x01;
    }
    uint32_t C = (permuted_key >> 28) & 0x0FFFFFFF;
    uint32_t D = permuted_key & 0x0FFFFFFF;
    for (int round = 0; round < 16; ++round) {
        C = left_circular_shift(C, SHIFTS[round]);
        D = left_circular_shift(D, SHIFTS[round]);
        uint64_t combined = ((uint64_t)C << 28) | (uint64_t)D;
        uint64_t subkey = 0;
        for (int i = 0; i < 48; ++i) {
            subkey <<= 1;
            subkey |= (combined >> (56 - PC2[i])) & 0x01;
        }
        for (int i = 0; i < 6; ++i) {
            subkeys[round][i] = (subkey >> (40 - 8 * i)) & 0xFF;
        }
    }
}
void print_subkeys(uint8_t subkeys[16][6]) {
    for (int i = 0; i < 16; ++i) {
        printf("Subkey %2d: ", i + 1);
        for (int j = 0; j < 6; ++j) {
            printf("%02X ", subkeys[i][j]);
        }
        printf("\n");
    }
}
int main() {
    uint8_t initial_key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t subkeys[16][6];
    generate_subkeys(initial_key, subkeys);
    print_subkeys(subkeys);
    return 0;
}
