#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK_SIZE 8
static const uint8_t IP[64] = { /* Initial Permutation */ };
static const uint8_t FP[64] = { /* Final Permutation */ };
static const uint8_t E[48] = { /* Expansion table */ };
static const uint8_t P[32] = { /* Permutation table */ };
static const uint8_t S[8][64] = { /* S-boxes */ };
void initial_permutation(uint8_t *block, uint8_t *out) { /* ... */ }
void final_permutation(uint8_t *block, uint8_t *out) { /* ... */ }
void expand(uint8_t *half_block, uint8_t *out) { /* ... */ }
void sbox(uint8_t *in, uint8_t *out) { /* ... */ }
void pbox(uint8_t *in, uint8_t *out) { /* ... */ }
void feistel(uint8_t *half_block, uint8_t *subkey, uint8_t *out) { /* ... */ }
void des_encrypt_block(uint8_t *block, uint8_t keys[16][48], uint8_t *out) { /* ... */ }
void des_set_key(uint8_t *key, uint8_t keys[16][48]) { /* ... */ }
void triple_des_encrypt_block(uint8_t *block, uint8_t keys[3][16][48], uint8_t *out) {
    uint8_t temp[BLOCK_SIZE];
    des_encrypt_block(block, keys[0], temp);
    des_encrypt_block(temp, keys[1], out);
    des_encrypt_block(out, keys[2], out);
}
void triple_des_set_key(uint8_t *key, uint8_t keys[3][16][48]) {
    des_set_key(key, keys[0]);
    des_set_key(key + 8, keys[1]);
    des_set_key(key + 16, keys[2]);
}
void pad(uint8_t *data, size_t len, size_t new_len) {
    data[len] = 0x80; 
    memset(data + len + 1, 0, new_len - len - 1);
}
void ecb_mode(uint8_t *plaintext, uint8_t *ciphertext, size_t len, uint8_t keys[3][16][48]) {
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        triple_des_encrypt_block(plaintext + i, keys, ciphertext + i);
    }
}
void cbc_mode(uint8_t *plaintext, uint8_t *ciphertext, size_t len, uint8_t keys[3][16][48], uint8_t *iv) {
    uint8_t buffer[BLOCK_SIZE];
    memcpy(buffer, iv, BLOCK_SIZE);
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            buffer[j] ^= plaintext[j + i];
        }
        triple_des_encrypt_block(buffer, keys, ciphertext + i);
        memcpy(buffer, ciphertext + i, BLOCK_SIZE);
    }
}
void cfb_mode(uint8_t *plaintext, uint8_t *ciphertext, size_t len, uint8_t keys[3][16][48], uint8_t *iv) {
    uint8_t buffer[BLOCK_SIZE];
    memcpy(buffer, iv, BLOCK_SIZE);
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        triple_des_encrypt_block(buffer, keys, buffer);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ buffer[j];
        }
        memcpy(buffer, ciphertext + i, BLOCK_SIZE);
    }
}
void print_hex(uint8_t *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}
int main() {
     uint8_t plaintext[16] = "This is a test!!";
    size_t len = 16;
    uint8_t padded_plaintext[24];
    uint8_t ciphertext[24];
    memset(padded_plaintext, 0, 24);
    memcpy(padded_plaintext, plaintext, len);
    uint8_t key[24] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1,
                       0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                       0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
    uint8_t iv[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    uint8_t keys[3][16][48];
    triple_des_set_key(key, keys);
    pad(padded_plaintext, len, 24);
    memset(ciphertext, 0, 24);
    ecb_mode(padded_plaintext, ciphertext, 24, keys);
    printf("ECB Mode Ciphertext: ");
    print_hex(ciphertext, 24);
    memset(ciphertext, 0, 24);
    cbc_mode(padded_plaintext, ciphertext, 24, keys, iv);
    printf("CBC Mode Ciphertext: ");
    print_hex(ciphertext, 24);
    memset(ciphertext, 0, 24);
    cfb_mode(padded_plaintext, ciphertext, 24, keys, iv);
    printf("CFB Mode Ciphertext: ");
    print_hex(ciphertext, 24);
    return 0;
}
