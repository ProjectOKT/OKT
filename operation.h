#ifndef OPERATION
#define OPERATION

#include "dtype.h"

int bi_compare(IN const bigint* A, IN const bigint* B);

word add_c(IN word src1, IN word src2, IN int* c);

msg add_same_sign(OUT bigint** dst, IN bigint* src1, IN bigint* src2);

msg bi_add(OUT bigint **dst, IN const bigint* src1, IN const bigint* src2);

word sub_adb(IN word A, IN char* borrow, IN word B);

msg bi_subc(OUT bigint** dst, IN bigint* src1, IN bigint* src2);

msg bi_sub(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_smul(OUT bigint** dst, IN word src1, IN word src2);

msg bi_mulc(OUT bigint** dst, IN bigint* src1, IN bigint* src2);

msg bi_mul(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_binary_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2);

msg bi_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2);
#endif