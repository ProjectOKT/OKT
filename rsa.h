#ifndef RSA_H
#define RSA_H

#include "dtype.h"

msg bi_is_composite(IN const bigint* n, IN const bigint* q, IN const bigint* a, IN int l);

msg bi_MillerRabinTest(IN const bigint* src, IN int testnum);

msg rsa_key_generation(OUT bigint** N, OUT bigint** e, OUT bigint** p, OUT bigint** q, OUT bigint** d, IN int bitlen);

msg rsa_encryption(OUT bigint** ciphertext, IN const bigint* msg, IN const bigint* e, IN const bigint* n);

msg rsa_decryption(OUT bigint** msg, IN const bigint* ciphertext, IN const bigint* d, IN const bigint* n);

#endif