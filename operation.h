#ifndef OPERATION
#define OPERATION

#include "dtype.h"

word add_c(word src1, word src2, int* c);
msg add_same_sign(bigint** dst, const bigint* src1, const bigint* src2);
msg bi_add(bigint **dst, bigint* src1, bigint* src2);
msg bi_compare(const bigint* A, const bigint* B);
word sub_adb(word A, char* borrow, word B);
msg bi_subc(bigint** dst, bigint* src1, bigint* src2);
msg bi_sub(bigint** dst, const bigint* src1, const bigint* src2);


#endif