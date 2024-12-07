#ifndef SUBOPERATION
#define SUBOPERATION

#include "dtype.h"

word add_c(IN word src1, IN word src2, IN int* c);
msg add_same_sign(OUT bigint** dst, IN bigint* src1, IN bigint* src2);
msg add_same_sign_replace(INOUT bigint** dst, IN bigint* src1);

word sub_adb(IN word A, IN char* borrow, IN word B);
msg bi_subc(OUT bigint** dst, IN bigint* src1, IN bigint* src2);
msg bi_smul(OUT bigint** dst, IN word src1, IN word src2);

msg bi_mulc(OUT bigint** dst, IN bigint* src1, IN bigint* src2);
msg bi_mul_k(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_binary_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2);

msg bi_squc(OUT bigint** dst, IN const word src1);

msg bi_word_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* A, IN const bigint* B);
msg bi_divc(OUT word* quotient, OUT bigint** remainder, IN const bigint* A, IN const bigint* B);
msg bi_divcc(OUT word* quotient, OUT bigint** remainder, IN const bigint* A, IN const bigint* B);
msg bi_2_word_div(OUT word* quotient,  IN const bigint* A, IN const word B);

msg bi_naive_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* A, IN const bigint* B);

#endif