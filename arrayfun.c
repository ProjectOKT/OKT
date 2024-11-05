#include <stdio.h>
#include <stdlib.h>

#include "arrayfun.h"
#include "params.h"
#include "dtype.h"
#include "errormsg.h"


/**
 * @brief Fills an array with random bytes.
 * 
 * This function populates the specified array (`dst`) with random byte values, 
 * where the length of the array is determined by the specified word length 
 * (`word_len`).
 * 
 * @param[out] dst Pointer to the array of `word` to be filled with random values.
 * @param[in] word_len The number of words to be filled with random data.
 * 
 * @return void
 */
void array_rand(OUT word* dst, IN int word_len)
{
    byte* p = (byte*)dst;
    
    int byte_index = word_len * sizeof(word);

    while(byte_index > 0)
    {
        *p = rand() & 0xff;
        p++;
        byte_index--;
    }
}

/**
 * @brief Initializes an array of words to zero.
 * 
 * This function sets all elements of the specified array (`a`) to zero, 
 * with the length of the array determined by `word_len`.
 * 
 * @param[out] a Pointer to the array of `word` to be initialized.
 * @param[in] word_len The length of the word array to be initialized.
 * 
 * @return void
 */
void array_init(OUT word* a, IN int word_len)
{
    for(int word_index = 0; word_index<word_len; word_index++)
    {
        a[word_index] = 0;
    }
}


/**
 * @brief Copies elements from the source array to the destination array.
 * 
 * This function copies `array_len` elements from the specified source array (`src_arr`) 
 * to the destination array (`dst_arr`). If the destination array is not NULL, it is 
 * initialized to zero before copying.
 * 
 * @param[out] dst_arr Pointer to the destination array of `word` where elements will be copied.
 * @param[in] src_arr Pointer to the source array of `word` from which elements will be copied.
 * @param[in] array_len The number of elements to copy from the source to the destination array.
 * 
 * @return void
 */
void array_copy(OUT word* dst_arr, IN const word* src_arr, IN int array_len)
{   
    
    if(dst_arr != NULL){
        array_init(dst_arr, array_len);
    }

    for(int index = 0; index < array_len; index++)
    {
        dst_arr[index] = src_arr[index];
    }
}