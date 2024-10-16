#ifndef BIGINTFUNC_H
#define BIGINTFUNC_H


#include "dtype.h"

msg bi_set_from_array(bigint** dst, int sign, int word_len, word* a);

msg bi_set_from_string(bigint** dst, const char* int_str, int base);

msg bi_get_random(bigint** dst, int sign, int word_len);

msg bi_print(bigint** dst, int base);

msg bi_new(bigint** dst, int word_len);

msg bi_delete(bigint** dst);

msg bi_refine(bigint* dst);

msg bi_assign(bigint** dst, bigint* src);


#endif