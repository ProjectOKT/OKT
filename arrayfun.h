#pragma once

#include "dtype.h"

void array_rand(const word* dst, int word_len);

void array_init(word* a, int word_len);

void array_copy(word* src_arr, word* dst_arr, int array_len);