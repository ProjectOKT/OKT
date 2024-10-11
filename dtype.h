#pragma once

#include <stdint.h>

typedef uint32_t msg;
// typedef unsigned int word;
// 컴퓨터 마다 unsigned int의 크기가 다를수 있기 때문에 uint32_t를 사용
// c99 이상 사용가능
typedef uint32_t word;

typedef struct {
    int sign;
    int word_len;
    word* a;
} bigint;
