#include <stdio.h>

#include <stdint.h>

#include <string.h>



typedef struct {

    uint32_t state[4];

    uint32_t count[2];

    unsigned char buffer[64];

} MD5_CTX;



void MD5Transform(uint32_t state[4], const unsigned char block[64]);

void MD5Init(MD5_CTX *context);

void MD5Update(MD5_CTX *context, const unsigned char *input, size_t inputLen);

void MD5Final(unsigned char digest[16], MD5_CTX *context);

void Encode(unsigned char *output, const uint32_t *input, size_t len);

void Decode(uint32_t *output, const unsigned char *input, size_t len);



unsigned char PADDING[64] = {

  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

};



void MD5Init(MD5_CTX *context) {

    context->count[0] = context->count[1] = 0;

    context->state[0] = 0x67452301;

    context->state[1] = 0xefcdab89;

    context->state[2] = 0x98badcfe;

    context->state[3] = 0x10325476;

}



void MD5Update(MD5_CTX *context, const unsigned char *input, size_t inputLen) {

    size_t i, index, partLen;



    index = (unsigned int)((context->count[0] >> 3) & 0x3F);

    if ((context->count[0] += ((uint32_t)inputLen << 3)) < ((uint32_t)inputLen << 3))

        context->count[1]++;

    context->count[1] += ((uint32_t)inputLen >> 29);

    partLen = 64 - index;



    if (inputLen >= partLen) {

        memcpy(&context->buffer[index], input, partLen);

        MD5Transform(context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64)

            MD5Transform(context->state, &input[i]);

        index = 0;

    } else {

        i = 0;

    }

    memcpy(&context->buffer[index], &input[i], inputLen - i);

}



void MD5Final(unsigned char digest[16], MD5_CTX *context) {

    unsigned char bits[8];

    unsigned int index, padLen;



    Encode(bits, context->count, 8);

    index = (unsigned int)((context->count[0] >> 3) & 0x3f);

    padLen = (index < 56) ? (56 - index) : (120 - index);

    MD5Update(context, PADDING, padLen);

    MD5Update(context, bits, 8);

    Encode(digest, context->state, 16);

    memset(context, 0, sizeof(*context));

}



void MD5Transform(uint32_t state[4], const unsigned char block[64]) {

    uint32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16];



    Decode(x, block, 64);

    /* Round 1 */

    // ... (full round transformations, omitted for brevity)



    state[0] += a;

    state[1] += b;

    state[2] += c;

    state[3] += d;

    memset(x, 0, sizeof(x));

}



void Encode(unsigned char *output, const uint32_t *input, size_t len) {

    for (size_t i = 0, j = 0; j < len; i++, j += 4) {

        output[j] = (unsigned char)(input[i] & 0xff);

        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);

        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);

        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);

    }

}



void Decode(uint32_t *output, const unsigned char *input, size_t len) {

    for (size_t i = 0, j = 0; j < len; i++, j += 4)

        output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |

                    (((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);

}



void printDigest(unsigned char digest[16]) {

    for (int i = 0; i < 16; i++)

        printf("%02x", digest[i]);

    printf("\n");

}



int main() {

    unsigned char digest[16];

    char message[] = "1000";

    MD5_CTX context;

    MD5Init(&context);

    MD5Update(&context, (unsigned char*)message, strlen(message));

    MD5Final(digest, &context);

    printf("MD5 (\"%s\") = ", message);

    printDigest(digest);

    return 0;

}

