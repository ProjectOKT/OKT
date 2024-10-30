#ifndef OPERATION
#define OPERATION

#include "dtype.h"

word add_c(word src1, word src2, int* c);
msg add_same_sign(bigint** dst, bigint* src1, bigint* src2);
msg bi_add(bigint *dst, bigint* src1, bigint* src2);
msg bi_compare(bigint** A, bigint** B);
word sub_adb(word A, char* borrow, word B);
msg bi_subc(bigint** dst, bigint** src1, bigint** src2);
msg bi_sub(bigint** dst, bigint** src1, bigint** src2);


#endif