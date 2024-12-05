#ifndef DTYPE_H
#define DTYPE_H


#include <stdint.h>
#include "params.h"

#define IN
#define OUT
#define INOUT

typedef int msg;        //return message
typedef uint8_t byte;

//define word type 
#if SIZEOFWORD == 32
    typedef uint16_t half_word;
    typedef uint32_t word;
#elif SIZEOFWORD == 64
    typedef uint32_t half_word;
    typedef uint64_t word;
#elif SIZEOFWORD == 8
    typedef byte word;
#endif

/**
 * @struct bigint
 * @brief A structure representing a big integer.
 *
 * This structure is used to store a large integer that can be
 * larger than the standard integer types. It contains the following
 * members:
 *
 * @param sign Indicates the sign of the big integer. 
 *             A value of 1 represents a positive number, 
 *             and a value of -1 represents a negative number.
 * @param word_len The number of words used to represent the big integer.
 * @param a Pointer to an array of words (of type word) that stores
 *          the actual digits of the big integer.
 */
typedef struct {
    int sign;      /**< The sign of the big integer. */
    int word_len;  /**< The number of words in the big integer. */
    word* a;       /**< Pointer to the array of words representing the big integer. */
} bigint;


#endif