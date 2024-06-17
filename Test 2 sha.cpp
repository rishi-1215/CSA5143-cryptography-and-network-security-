#include <stdint.h>

#include<stdio.h>

#include <stdlib.h>

#include <string.h>



#define SHA256_BLOCK_SIZE 1024

#define SHA256_WORD_SIZE 32

#define SHA256_ROUNDS 64



typedef uint32_t sha256_word_t;



void sha256_extend_words(sha256_word_t W[16], sha256_word_t W_ext[64]) {

    int i;

    for (i = 0; i < 16; i++) {

        W_ext[i] = W[i];

    }

    for (i = 16; i < 64; i++) {

        W_ext[i] = (sha256_word_t)((W_ext[i - 2] >> 7 | W_ext[i - 2] << 25) +

                                   W_ext[i - 7] +

                                   (W_ext[i - 15] >> 6 | W_ext[i - 15] << 26) +

                                   W_ext[i - 16]);

    }

}



void sha256_single_round(sha256_word_t h[8], sha256_word_t W_ext[64], int i) {

    sha256_word_t e, f, g, Sigma1, Ch;

    e = h[0];

    f = h[1];

    g = h[2];

    Sigma1 = (e >> 6) | (e << 26);

    Ch = (e & f) ^ (~e & g);

    h[0] = (h[0] + Sigma1 + Ch + W_ext[i]) & 0xFFFFFFFF;

    h[1] = (h[1] + h[0]) & 0xFFFFFFFF;

    h[2] = (h[2] + h[1]) & 0xFFFFFFFF;

    h[3] = (h[3] + h[2]) & 0xFFFFFFFF;

    h[4] = (h[4] + h[3]) & 0xFFFFFFFF;

    h[5] = (h[5] + h[4]) & 0xFFFFFFFF;

    h[6] = (h[6] + h[5]) & 0xFFFFFFFF;

    h[7] = (h[7] + h[6]) & 0xFFFFFFFF;

}



int main() {

    uint8_t message[SHA256_BLOCK_SIZE] = { /* 1024-bit input message */ };

    sha256_word_t W[16];

    sha256_word_t W_ext[64];

    sha256_word_t h[8] = { /* initial hash value */ };

    int i;

    for (i = 0; i < 16; i++) {

        W[i] = (message[i * 4 + 0] << 24) |

               (message[i * 4 + 1] << 16) |

               (message[i * 4 + 2] << 8) |

               message[i * 4 + 3];

    }

    sha256_extend_words(W, W_ext);

    for (i = 0; i < 64; i++) {

        sha256_single_round(h, W_ext, i);

    }

    for (i = 0; i < 8; i++) {

        printf("%08x", h[i]);

    }

    printf("\n");



    return 0;

}
