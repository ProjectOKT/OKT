#ifndef OPERATION
#define OPERATION

#include "dtype.h"
#include "operation_tool.h"

msg bi_add(OUT bigint **dst, IN const bigint* src1, IN const bigint* src2);

msg bi_add_replace(INOUT bigint** dst, IN const bigint* src1);

msg bi_sub(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_mul(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

int get_sign(bigint* src);

msg bi_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2);

msg bi_mul_kara(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2);

msg bi_squ(OUT bigint** dst, IN const bigint* src1);

msg bi_squ_kara(OUT bigint** dst, IN const bigint* src);

msg bi_mod_exp_l2r(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod);

msg bi_mod_exp_r2l(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod);

msg bi_mod_exp_MaS(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod);

msg bi_bar_redu(OUT bigint** dst, IN const bigint* A, IN const bigint* T, IN const bigint* N);

#endif