#include <stdio.h>

#include <stdint.h>

#include <stdlib.h>

#include <string.h>

#include <openssl/des.h>

void print_hex(uint8_t *data, int len) {

    for (int i = 0; i < len; i++) {

        printf("%02X", data[i]);

    }

    printf("\n");

}

void encrypt_3des_ecb(uint8_t *plaintext, uint8_t *ciphertext, size_t len, DES_key_schedule ks1, DES_key_schedule ks2, DES_key_schedule ks3) {

    for (size_t i = 0; i < len; i += 8) {

        DES_ecb3_encrypt((DES_cblock*)(plaintext + i), (DES_cblock*)(ciphertext + i), &ks1, &ks2, &ks3, DES_ENCRYPT);

    }

}

    uint8_t plaintext[16] = "This is a test!!";

    size_t len = sizeof(plaintext);

    uint8_t key[24] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1,

                       0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,

                       0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};

    uint8_t ciphertext[len];

    memset(ciphertext, 0, len);

    DES_key_schedule ks1, ks2, ks3;

    DES_set_key((DES_cblock*)(key), &ks1);

    DES_set_key((DES_cblock*)(key + 8), &ks2);

    DES_set_key((DES_cblock*)(key + 16), &ks3);

    encrypt_3des_ecb(plaintext, ciphertext, len, ks1, ks2, ks3);

    printf("Plaintext:  %s\n", plaintext);

    printf("Ciphertext: ");

    print_hex(ciphertext, len);

    return 0;

}

