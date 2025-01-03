#ifndef BIGINTFUNC_H
#define BIGINTFUNC_H

#include <stdio.h>
#include "dtype.h"

msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN const word* a);

msg bi_set_from_string(OUT bigint** dst, IN const char* int_str, IN int base);

msg bi_get_random(OUT bigint** dst, IN int sign, IN int word_len);

msg bi_get_random_within_range(OUT bigint** dst, IN bigint* lower_bound, IN bigint* upper_bound);

msg bi_print(IN const bigint* src, IN int base);

msg bi_fprint(IN FILE* file, IN bigint* src);

msg bi_new(OUT bigint** dst, IN int word_len);

msg bi_delete(OUT bigint** dst);

msg bi_refine(OUT bigint* dst);

msg bi_assign(OUT bigint** dst, IN const bigint* src);

msg bi_fillzero(OUT bigint* dst, IN int src_len, IN int toward);

msg bi_connect(OUT bigint** dst, IN bigint* src1, IN bigint* src2);

msg bi_bit_rshift(OUT bigint* dst, IN int num_bits);

msg bi_bit_lshift(OUT bigint* dst, IN int num_bits);

int bi_compare(IN const bigint* A, IN const bigint* B);

msg bi_gcd(OUT bigint** gcd, IN const bigint* src1, IN const bigint* src2);

msg bi_EEA(OUT bigint** gcd, OUT bigint** x, OUT bigint** y, IN const bigint* src1, IN const bigint* src2);

#endif