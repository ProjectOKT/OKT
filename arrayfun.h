#ifndef ARRAYFUNC_H
#define ARRAYFUNC_H

#include "dtype.h"

void array_rand(const word* dst, int word_len);

void array_init(word* a, int word_len);

void array_copy(word* dst_arr, word* src_arr, int array_len);

#endif