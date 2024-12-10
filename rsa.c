#include <stdio.h>


#include "operation.h"
#include "bigintfun.h"
#include "params.h"
#include "errormsg.h"


/***********************************************
 * Composite Check using Modular Exponentiation
 ***********************************************/
/**
 * @brief Checks if a number is composite using modular exponentiation and the Miller-Rabin test logic.
 * 
 * This function performs a composite check on the number `n` using the divisor `q`, witness `a`, 
 * and a parameter `l` that determines the number of iterations. It computes modular exponentiation
 * and verifies conditions to determine compositeness:
 * 
 * - If `a^q % n == 1`, the test concludes "NOT Composite".
 * - For each iteration, if `a^(2^j * q) % n == n-1`, the test concludes "NOT Composite".
 * - If neither condition is met after all iterations, the test concludes "Composite".
 * 
 * @param[in] n The bigint number to be tested for compositeness.
 * @param[in] q A bigint representing the divisor used in the composite test.
 * @param[in] l The maximum iteration count for the test.
 * @param[in] a The witness bigint used to test compositeness.
 * 
 * @return Returns "Composite" if the number is composite, "NOT Composite" otherwise.
 *         Error handling is not explicitly described in the implementation.
 */
msg bi_is_composite(IN const bigint* n, IN const bigint* q, IN const bigint* a, IN int l)
{
    if((n == NULL) || (q == NULL) || (a == NULL) || (n->a == NULL) || (q->a == NULL) || (a->a == NULL) ||
    (n->sign != POSITIVE) || (q->sign != POSITIVE) || (a->sign != POSITIVE) || (n->word_len <= 0) || (q->word_len <= 0) || (a->word_len <= 0) || (l <= 0))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }
    bigint* buf1 = NULL;
    bigint* buf2 = NULL;
    bigint* a_buf = NULL;
    bigint* n_minus_1 = NULL;

    bi_new(&buf1, 1);
    buf1->sign = POSITIVE;
    buf1->a[0] = 1;
    bi_sub(&n_minus_1, n, buf1);

#if SECURE_SCA == 1
    bi_mod_exp_MaS(&a_buf, a, q, n);
#elif
    bi_mod_exp_l2r(&a_buf, a, q, n);
#endif
    if(a_buf->sign == ZERO)
    {
        bi_delete(&buf1);
        bi_delete(&buf2);
        bi_delete(&a_buf);
        bi_delete(&n_minus_1);
        return COMPOSITE;
    }
    if(bi_compare(a_buf, buf1) == 0)
    {
        bi_delete(&buf1);
        bi_delete(&buf2);
        bi_delete(&a_buf);
        bi_delete(&n_minus_1);
        return !COMPOSITE;
    }

    buf1->a[0] = 2;
    for (int j = 0; j < l; j++)
    {   
        if (bi_compare(a_buf, n_minus_1) == 0)
        {
            bi_delete(&buf1);
            bi_delete(&buf2);
            bi_delete(&a_buf);
            bi_delete(&n_minus_1);

            return !COMPOSITE;
        }
#if SECURE_SCA == 1
    bi_mod_exp_MaS(&buf2, a_buf, buf1, n);
#elif
    bi_mod_exp_l2r(&buf2, a_buf, buf1, n);
#endif
        
        bi_assign(&a_buf, buf2);
    }
    bi_delete(&buf1);
    bi_delete(&buf2);
    bi_delete(&a_buf);
    bi_delete(&n_minus_1);

    return COMPOSITE;
}


/***********************************************
 * Primality Test: Miller-Rabin
 ***********************************************/
/**
 * @brief Performs a Miller-Rabin primality test on the given number.
 * 
 * This function tests whether the input bigint `src` is a prime number by conducting `testnum` rounds
 * of the Miller-Rabin probabilistic primality test. If the function returns 0, the number is composite.
 * If it returns 1, the number is probably prime.
 * 
 * @param[in] src The bigint number to be tested for primality.
 * @param[in] testnum The number of test rounds to perform for greater accuracy.
 * 
 * @return Returns 1 if the number is probably prime, 0 if it is composite.
 */
msg bi_MillerRabinTest(IN const bigint* src, IN int testnum)
{
    if((src == NULL) || (src->a == NULL) || (src->sign != POSITIVE) || (src->word_len <= 0))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    if((src->word_len == 1) && (src->a[0] == 2))
    {
        return PROBABLY_PRIME;
    }
    else if ((src->a[0] & 1) == 0)
    {
        return COMPOSITE;
    }

    bigint* q = NULL;
    bigint* n_minus_1 = NULL;
    bigint* one = NULL;
    bigint* a = NULL;
    int l = 0;

    bi_new(&one, 1);
    one->sign = POSITIVE;
    one->a[0] = 1;
    bi_sub(&n_minus_1, src, one);
    bi_assign(&q, n_minus_1);
    while((q->a[0] & 1) == 0)
    {
        bi_bit_rshift(q, 1);
        l++;
    }

    while (testnum > 0)
    {   
        bi_get_random_within_range(&a, one, n_minus_1);
        if(bi_is_composite(src, q, a, l) == COMPOSITE)
        {
            bi_delete(&q);
            bi_delete(&n_minus_1);
            bi_delete(&one);
            bi_delete(&a);
            return COMPOSITE;
        }
        testnum--;
    }
    bi_delete(&q);
    bi_delete(&n_minus_1);
    bi_delete(&one);
    bi_delete(&a);

    return PROBABLY_PRIME;
}


/***********************************************
 * RSA Key Generation
 ***********************************************/
/**
 * @brief Generates RSA key pairs (N, e, d) and the prime factors (p, q).
 * 
 * This function generates a pair of RSA keys, including the modulus `N`, public exponent `e`, 
 * private exponent `d`, and the prime factors `p` and `q`. The bit length of the modulus is specified
 * by the `bitlen` parameter.
 * 
 * @param[out] N Pointer to the bigint that will hold the modulus (N = p * q).
 * @param[out] e Pointer to the bigint that will hold the public exponent.
 * @param[out] p Pointer to the bigint that will hold the first prime factor.
 * @param[out] q Pointer to the bigint that will hold the second prime factor.
 * @param[out] d Pointer to the bigint that will hold the private exponent.
 * @param[in] bitlen The desired bit length of the modulus `N`.
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid bit length or memory allocation error).
 */
msg rsa_key_generation(OUT bigint** N, OUT bigint** e, OUT bigint** p, OUT bigint** q, OUT bigint** d, IN int bitlen)
{
    if((bitlen < 2) || (bitlen % 2 != 0))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }
    bigint* lower_bound = NULL;
    bigint* upper_bound = NULL;
    bigint* one = NULL;
    bigint* buf1 = NULL;
    bigint* buf2 = NULL;
    bigint* phi_n = NULL;

    bi_new(&one, 1);
    one->sign = POSITIVE;
    one->a[0] = 1;
    
    bi_new(&buf1, 1);
    buf1->sign = POSITIVE;
    buf1->a[0] = 1;
    bi_bit_lshift(buf1, bitlen/2 - 1);
    bi_assign(&lower_bound, buf1);
    bi_bit_lshift(buf1, 1);
    bi_assign(&upper_bound, buf1);
    //Choose two random distinct n/2-bit primes p and q
    do {
        printf("searching for prime p...\n");
        do{
            bi_get_random_within_range(p, lower_bound, upper_bound);
        }while(bi_MillerRabinTest(*p, MILLER_NUM) != PROBABLY_PRIME);
        
        printf("searching for prime q...\n");
        do{
            bi_get_random_within_range(q, lower_bound, upper_bound);
        }while(bi_MillerRabinTest(*q, MILLER_NUM) != PROBABLY_PRIME);
    }while(bi_compare(*p, *q) == 0);

    // Calculate N = p x q
    bi_mul_kara(N, *p, *q); 

    // Calculate Pi_n = (p-1)(q-1)
    bi_sub(&buf1, *p, one);
    bi_sub(&buf2, *q, one);
    bi_mul_kara(&phi_n, buf1, buf2);

    // Choose e such that gcd(e, (p-1)(q-1)) = 1
    do{
        bi_get_random_within_range(e, one, phi_n);
        bi_gcd(&buf1, *e, phi_n);
    }while(bi_compare(buf1, one) != 0); 

    // Calculate d such that ed = 1 mod (phi_n)
    bi_EEA(&buf1, d, &buf2, *e, phi_n);
    if(((*d)->sign) == NEGATIVE)
    {
        bi_add(d, *d, phi_n);
    }

    bi_delete(&lower_bound);
    bi_delete(&upper_bound);
    bi_delete(&one);
    bi_delete(&buf1);
    bi_delete(&buf2);
    bi_delete(&phi_n);

    return SUCCESS;
}


/***********************************************
 * RSA Encryption
 ***********************************************/
/**
 * @brief Encrypts a message using the RSA public key.
 * 
 * This function encrypts the input message `msg` using the RSA algorithm. It uses the public key 
 * (e, N) to compute the ciphertext as `ciphertext = msg^e mod N`.
 * 
 * @param[out] ciphertext Pointer to the bigint that will hold the encrypted message.
 * @param[in] msg The input bigint message to be encrypted.
 * @param[in] e The public exponent bigint.
 * @param[in] n The modulus bigint.
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid inputs or memory allocation error).
 */
msg rsa_encryption(OUT bigint** ciphertext, IN const bigint* msg, IN const bigint* e, IN const bigint* n)
{
    if((msg == NULL) || (e == NULL) || (n == NULL) || (msg->a == NULL) || (e->a == NULL) || (n->a == NULL) 
    || (msg->sign != POSITIVE) || (e->sign != POSITIVE) || (n->sign != POSITIVE) || (msg->word_len <= 0)|| (e->word_len <= 0)|| (n->word_len <= 0))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }
    // C = M^e mod N
    bi_mod_exp_l2r(ciphertext, msg, e, n);

    return SUCCESS;
}


/***********************************************
 * RSA Decryption
 ***********************************************/
/**
 * @brief Decrypts a ciphertext using the RSA private key.
 * 
 * This function decrypts the input ciphertext `ciphertext` using the RSA algorithm. It uses the private key 
 * (d, N) to compute the original message as `msg = ciphertext^d mod N`.
 * 
 * @param[out] msg Pointer to the bigint that will hold the decrypted message.
 * @param[in] ciphertext The input bigint ciphertext to be decrypted.
 * @param[in] d The private exponent bigint.
 * @param[in] n The modulus bigint.
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid inputs or memory allocation error).
 */
msg rsa_decryption(OUT bigint** msg, IN const bigint* ciphertext, IN const bigint* d, IN const bigint* n)
{
    if((ciphertext == NULL) || (d == NULL) || (n == NULL) || (ciphertext->a == NULL) || (d->a == NULL) || (n->a == NULL) 
    || (ciphertext->sign != POSITIVE) || (d->sign != POSITIVE) || (n->sign != POSITIVE) || (ciphertext->word_len <= 0)|| (d->word_len <= 0)|| (n->word_len <= 0))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }
    // M = C^d mod N
#if SECURE_SCA == 1
    bi_mod_exp_MaS(msg, ciphertext, d, n);
#elif
    bi_mod_exp_l2r(msg, ciphertext, d, n);
#endif

    return SUCCESS;
}