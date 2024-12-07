#include <stdio.h>


#include "operation.h"
#include "bigintfun.h"
#include "params.h"
#include "errormsg.h"

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

    bi_mod_exp_l2r(&a_buf, a, q, n);
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
        bi_mod_exp_l2r(&buf2, a_buf, buf1, n);
        bi_assign(&a_buf, buf2);
    }
    bi_delete(&buf1);
    bi_delete(&buf2);
    bi_delete(&a_buf);
    bi_delete(&n_minus_1);

    return COMPOSITE;
}

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
    //Choose two random distinct n/2-bit primes p and q 필요
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

    bi_mul_kara(N, *p, *q); // Calculate N = p x q

    bi_sub(&buf1, *p, one);
    bi_sub(&buf2, *q, one);
    bi_mul_kara(&phi_n, buf1, buf2); // Calculate Pi_n = (p-1)(q-1)

    do{
        bi_get_random_within_range(e, one, phi_n);
        bi_gcd(&buf1, *e, phi_n);
    }while(bi_compare(buf1, one) != 0); // Choose e such that gcd(e, (p-1)(q-1)) = 1

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


msg rsa_encryption(OUT bigint** ciphertext, IN const bigint* msg, IN const bigint* e, IN const bigint* n)
{
    if((msg == NULL) || (e == NULL) || (n == NULL) || (msg->a == NULL) || (e->a == NULL) || (n->a == NULL) 
    || (msg->sign != POSITIVE) || (e->sign != POSITIVE) || (n->sign != POSITIVE) || (msg->word_len <= 0)|| (e->word_len <= 0)|| (n->word_len <= 0))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }
    bi_mod_exp_l2r(ciphertext, msg, e, n);

    return SUCCESS;
}


msg rsa_decryption(OUT bigint** msg, IN const bigint* ciphertext, IN const bigint* d, IN const bigint* n)
{
    if((ciphertext == NULL) || (d == NULL) || (n == NULL) || (ciphertext->a == NULL) || (d->a == NULL) || (n->a == NULL) 
    || (ciphertext->sign != POSITIVE) || (d->sign != POSITIVE) || (n->sign != POSITIVE) || (ciphertext->word_len <= 0)|| (d->word_len <= 0)|| (n->word_len <= 0))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }
    bi_mod_exp_l2r(msg, ciphertext, d, n);

    return SUCCESS;
}