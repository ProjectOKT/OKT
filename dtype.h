#ifndef DTYPE_H
#define DTYPE_H


#include <stdint.h>

typedef uint32_t msg;
typedef uint8_t byte;
typedef uint32_t word;

typedef struct {
    int sign;
    int word_len;
    word* a;
} bigint;


#endif