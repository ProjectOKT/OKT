#ifndef OPERATION
#define OPERATION

#include "dtype.h"

int bi_compare(IN const bigint* A, IN const bigint* B);

word add_c(IN word src1, IN word src2, IN int* c);

msg add_same_sign(OUT bigint** dst, IN bigint* src1, IN bigint* src2);

msg add_same_sign_replace(INOUT bigint** dst, IN bigint* src1);

msg bi_add(OUT bigint **dst, IN const bigint* src1, IN const bigint* src2);

msg bi_add_replace(INOUT bigint** dst, IN const bigint* src1);

word sub_adb(IN word A, IN char* borrow, IN word B);

msg bi_subc(OUT bigint** dst, IN bigint* src1, IN bigint* src2);

msg bi_sub(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_smul(OUT bigint** dst, IN word src1, IN word src2);

msg bi_mulc(OUT bigint** dst, IN bigint* src1, IN bigint* src2);

msg bi_mul(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_binary_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2);

msg bi_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2);

msg bi_mul_k(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_mul_kara(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_squc(OUT bigint** dst, IN const word src1);

msg bi_squ(OUT bigint** dst, IN const bigint* src1);

msg bi_squ_kara(OUT bigint** dst, IN const bigint* src);

msg bi_mod_exp_l2r(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod);

msg bi_mod_exp_r2l(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod);

msg bi_mod_exp_MaS(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod);

#endif