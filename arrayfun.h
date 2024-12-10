#ifndef ARRAYFUNC_H
#define ARRAYFUNC_H

#include "dtype.h"

void array_rand(OUT word* dst, IN int word_len);

void array_init(OUT word* a, IN int word_len);

void array_copy(OUT word* dst_arr, IN const word* src_arr, IN int array_len);

#endif