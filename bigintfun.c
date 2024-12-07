#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"
#include "bigintfun.h"
#include "errormsg.h"
#include "dtype.h"
#include "arrayfun.h"
#include "operation.h"

/**
 * @brief Initializes a bigint structure from an array of words.
 * 
 * This function converts an array of words into a `bigint` structure and stores it in the specified location.
 * 
 * @param[out] dst Pointer to a double pointer of `bigint`, where the converted bigint will be stored.
 * @param[in] sign The sign of the bigint (POSITIVE or NEGATIVE).
 * @param[in] word_len The length of the input array.
 * @param[in] a Pointer to the input array of words.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN const word* a)
{
    bi_new(dst, word_len);
    for (int i = 0; i < word_len; i++){
        (*dst) -> a[i] = a[i];
    }
    (*dst) -> sign = sign;

    return SUCCESS;
}

/**
 * @brief Converts a string to a bigint structure.
 * 
 * This function converts a given string representation of an integer into a `bigint` structure.
 * 
 * @param[out] dst Pointer to a double pointer of `bigint`, where the converted bigint will be stored.
 * @param[in] int_str Pointer to the input string representing the integer.
 * @param[in] base The base of the input string (valid values are 2, 16).
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_set_from_string(OUT bigint** dst, IN const char* int_str, IN int base)
{
    int word_len = 0;
    unsigned int strlength = 0; 
    if (base == 2){
        if (int_str[0] == '-'){
            strlength = strlen(int_str) - 1;
            word_len = strlength % SIZEOFWORD == 0 ? strlength / SIZEOFWORD : strlength / SIZEOFWORD +1;
            bi_new(dst, word_len);
            (*dst) -> sign = NEGATIVE;
            for (unsigned int i = 0; i < strlength; i++){
                if (int_str[strlength - i] == '1'){
                    (*dst) -> a[i/SIZEOFWORD] |= (word)1 << (i % SIZEOFWORD);
                }
                else if (int_str[strlength - i] != '0'){
                    fprintf(stderr, ERR_INVALID_INPUT);
                    bi_delete(dst);
                    return FAILED;
                }
            }
        }
        else{
            strlength = strlen(int_str);
            word_len = strlength % SIZEOFWORD == 0 ? strlength / SIZEOFWORD : strlength / SIZEOFWORD +1;
            bi_new(dst, word_len);
            (*dst) -> sign = POSITIVE;
            for (unsigned int i = 0; i < strlength; i++){
                if (int_str[strlength - i - 1] == '1'){
                    (*dst) -> a[i/SIZEOFWORD] |= (word)1 << (i % SIZEOFWORD);
                }
                else if (int_str[strlength - i - 1] != '0'){
                    fprintf(stderr, ERR_INVALID_INPUT);
                    bi_delete(dst);
                    return FAILED;
                }
            }
        }
        
    }
    else if (base == 16){
        if (int_str[0] == '-'){
            strlength = strlen(int_str)-1;
            word_len = strlength * 4 % SIZEOFWORD == 0 ? strlength * 4 / SIZEOFWORD : strlength * 4 / SIZEOFWORD +1;  
            bi_new(dst, word_len);
            (*dst)->sign = NEGATIVE;
            for (unsigned int i = 0; i < strlength; i++) {
                char c = int_str[strlength - i];
                int digit = 0;
            
                if (c >= '0' && c <= '9') {
                    digit = c - '0';
                } else if (c >= 'a' && c <= 'f') {
                    digit = c - 'a' + 10;
                } else if (c >= 'A' && c <= 'F') {
                    digit = c - 'A' + 10;
                }
                else{
                    fprintf(stderr, ERR_INVALID_INPUT);
                    bi_delete(dst);
                    return FAILED;
                }
                (*dst)->a[i * 4 / SIZEOFWORD] |= (word)(digit & 0xF) << (i * 4 % SIZEOFWORD);
            }
        }
        else {
            strlength = strlen(int_str); 
            word_len = strlength * 4 % SIZEOFWORD == 0 ? strlength * 4 / SIZEOFWORD : strlength * 4 / SIZEOFWORD +1;  
            bi_new(dst, word_len);
            (*dst)->sign = POSITIVE;
            for (unsigned int i = 0; i < strlength; i++) {
                char c = int_str[strlength - i - 1];
                int digit = 0;

                if (c >= '0' && c <= '9') {
                    digit = c - '0';
                } else if (c >= 'a' && c <= 'f') {
                    digit = c - 'a' + 10;
                } else if (c >= 'A' && c <= 'F') {
                    digit = c - 'A' + 10;
                }
                else{
                    fprintf(stderr, ERR_INVALID_INPUT);
                    bi_delete(dst);
                    return FAILED;
                }
                (*dst)->a[i * 4 / SIZEOFWORD] |= (word)(digit & 0xF) << (i * 4 % SIZEOFWORD);
            }
        }
    }
    else {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }
    bi_refine(*dst);

    return SUCCESS;
}


/**
 * @brief Generates a random bigint and stores it in a bigint structure.
 * 
 * This function creates a random bigint and saves it in the specified bigint structure.
 * 
 * @param[out] dst Pointer to a double pointer of `bigint`, where the generated random bigint will be stored.
 * @param[in] sign The sign of the bigint (POSITIVE or NEGATIVE).
 * @param[in] word_len The length of the random array to be generated.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_get_random(OUT bigint** dst, IN int sign, IN int word_len)
{
    msg err_code = 0;
    err_code = bi_new(dst, word_len);
    if (err_code == FAILED)
    {
        return FAILED;
    }

    (*dst) -> sign = sign;
    
    while(!((*dst)->a[word_len - 1])) // last word nonzero
    {
        array_rand((*dst)->a, word_len);
    }

    return SUCCESS;
}


/***********************************************
 * Random Number within Range
 ***********************************************/
/**
 * @brief Generates a random bigint within a specified range.
 * 
 * This function generates a random bigint that lies within the range defined by the 
 * `lower_bound` and `upper_bound` (inclusive). It ensures the generated number is uniformly
 * distributed within the given range.
 * 
 * @param[out] dst Pointer to the bigint that will hold the generated random number.
 * @param[in] lower_bound The lower bound of the range (inclusive).
 * @param[in] upper_bound The upper bound of the range (inclusive).
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid range, invalid input, or memory allocation error).
 */
msg bi_get_random_within_range(OUT bigint** dst, IN bigint* lower_bound, IN bigint* upper_bound)
{
    if((lower_bound == NULL) || (upper_bound == NULL) || (lower_bound->a == NULL) || (upper_bound->a == NULL) || (lower_bound->word_len <= 0) 
    || (upper_bound->word_len <= 0))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    bigint* range = NULL;
    bigint* random_range = NULL;
    int word_len = 0;
    int byte_len = 0;
    byte rand_byte = 0;

    bi_sub(&range, upper_bound, lower_bound);
    word_len = range->word_len;
    bi_new(&random_range, word_len);
    random_range->sign = POSITIVE;
    for (byte_len = (int)sizeof(word) - 1; byte_len > 0; byte_len--)
    {
        if(((range->a[word_len - 1] >> (8 * byte_len)) & (byte)0xff) != 0)
        {
            break;
        }
    }
    if(word_len > 0)
    {
        array_rand(random_range->a, word_len - 1);
    }
    
    for(int byte_index = 0; byte_index < byte_len; byte_index++)
    {
        random_range->a[word_len - 1] ^= (((word)(rand() & 0xff)) << (8 * byte_index));
    }
    rand_byte = (rand() & 0xff) % ((range->a[word_len - 1] >> (8 * byte_len)) & 0xff);
    random_range->a[word_len - 1] ^= ((word)(rand_byte) << (8 * byte_len));
    bi_refine(random_range);

    bi_add(dst, lower_bound, random_range);
    bi_delete(&range);
    bi_delete(&random_range);

    return SUCCESS;
}


/**
 * @brief Prints a bigint in the specified base.
 * 
 * This function takes a bigint structure and outputs its value in the specified numerical base.
 * 
 * @param[in] src Pointer to the `bigint` structure to be printed.
 * @param[in] base The base in which to print the bigint (valid values are 2, 16).
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_print(IN const bigint* src, IN int base)
{
    int temp = 0;

    if((src == NULL) || !(base == 2 || base == 10 || base == 16))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }
    if(src->sign == ZERO) // print ZERO
    {
        printf("ZERO\n");
        return SUCCESS;
    }

    if(base == 2)
    {
        if(src->sign == POSITIVE)
        {
            printf("0b");
        }
        else if(src->sign == NEGATIVE)
        {
            printf("-0b");
        }
        else
        {
            return FAILED;
        }
        
        temp = sizeof(word) * 8;
        while(temp)
        {
            if((src->a[src->word_len - 1] >> (temp - 1) & 0x01))
            {
                break;
            }
            temp--;
        }
        for(int bit_index = temp - 1; bit_index >=0; bit_index--)
        {
            printf("%1u", (byte)((src->a[src->word_len - 1]) >> bit_index) & 0x01);
        }

        for(int word_index = src->word_len - 1; word_index > 0 ; word_index--)
        {
            for(int bit_index = 8 * sizeof(word) - 1; bit_index >=0 ; bit_index--)
            {
                printf("%1u", (byte)((src->a[word_index - 1]) >> bit_index) & 0x01);
            }
        }
        printf("\n");

        return SUCCESS;
    }
    else if(base == 16)
    {
        if(src->sign == POSITIVE)
        {
            printf("0x");
        }
        else if(src->sign == NEGATIVE)
        {
            printf("-0x");
        }
        else
        {
            fprintf(stderr, ERR_INVALID_INPUT);
            return FAILED;
        }

        temp = sizeof(word) * 2;
        while(temp)
        {
            if((src->a[src->word_len - 1] >> (temp - 1) * 4) & 0xf)
            {
                break;
            }
            temp--;
        }
        for(int byte_index = temp; byte_index > 0; byte_index--)
        {
            printf("%01x", (byte)((src->a[src->word_len - 1] >> ((byte_index - 1) * 4)) & 0xf));
        }
        for(int word_index = src->word_len - 1; word_index > 0; word_index--)
        {
            for(int byte_index = sizeof(word); byte_index > 0; byte_index--)
            {
                printf("%02x", (byte)((src->a[word_index - 1] >> ((byte_index - 1) * 8)) & 0xff));
            }
        }
        printf("\n");

        return SUCCESS;
    }

    return FAILED;
}


/**
 * @brief Prints a bigint to a specified file.
 * 
 * This function takes a bigint structure and writes its value to the provided file.
 * 
 * @param[in] file Pointer to the `FILE` where the bigint will be printed.
 * @param[in] src Pointer to the `bigint` structure to be printed.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_fprint(IN FILE* file, IN bigint* src)
{
    int temp = 0;

    if (src == NULL) {
        fprintf(stderr, "Error: NULL pointer dereference in bi_fprint\n");
        return FAILED;
    }
    if(src->sign == ZERO)
    {
        fprintf(file, "0x0\n");
        return SUCCESS;
    }
    else if(src->sign == POSITIVE)
    {
        fprintf(file, "0x");
    }
    else if(src->sign == NEGATIVE)
    {
        fprintf(file, "-0x");
    }
    else
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    if (src->a == NULL) {
        fprintf(stderr, "Error: NULL pointer dereference for bigint array in bi_fprint\n");
        return FAILED;
    }

    temp = sizeof(word) * 2;
    while(temp)
    {
        if((src->a[src->word_len - 1] >> (temp - 1) * 4) & 0xf)
        {
            break;
        }
        temp--;
    }

    for(int byte_index = temp; byte_index > 0; byte_index--)
    {
        fprintf(file, "%01x", (byte)((src->a[src->word_len - 1] >> ((byte_index - 1) * 4)) & 0xf));
    }
    for(int word_index = src->word_len - 1; word_index > 0; word_index--)
    {
        for(int byte_index = sizeof(word); byte_index > 0; byte_index--)
        {
            fprintf(file, "%02x", (byte)((src->a[word_index - 1] >> ((byte_index - 1) * 8)) & 0xff));
        }
    }
    fprintf(file, "\n");

    return SUCCESS;
}


/**
 * @brief Allocates a new bigint with a specified word length.
 * 
 * This function allocates memory for a new `bigint` structure with an array size equal to the specified word length.
 * 
 * @param[out] dst Pointer to a double pointer of `bigint`, where the allocated bigint will be stored.
 * @param[in] word_len The length of the array to be allocated for the bigint.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_new(OUT bigint** dst, IN int word_len)
{
    if(*dst != NULL)
    {
        bi_delete(dst);
    }
    
    (*dst) = (bigint*)calloc(1, sizeof(bigint));
    if((*dst) == NULL)
    {
        fprintf(stderr, ERR_MEMORY_ALLOCATION);
        return FAILED;
    }

    (*dst) -> sign = ZERO;
    (*dst) -> word_len = word_len;
    (*dst) -> a = (word*)calloc(word_len, sizeof(word));

    if((*dst) -> a == NULL)
    {
        fprintf(stderr, ERR_MEMORY_ALLOCATION);
        bi_delete(dst);
        return FAILED;
    }

    return SUCCESS;
}


/**
 * @brief Deletes a bigint structure and frees allocated memory.
 * 
 * This function deallocates the memory associated with the specified `bigint` structure.
 * 
 * @param[out] dst Pointer to a double pointer of `bigint`, which will be deleted.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_delete(OUT bigint** dst)
{
    if((*dst) == NULL)
    {
        return SUCCESS;
    }
#if ZERORIZE == 1
    array_init((*dst)->a, (*dst)->word_len);
    (*dst)->sign = 0;
    (*dst)->word_len = 0;
#endif
    free((*dst)->a);
    free((*dst));
    (*dst) = NULL;

    return SUCCESS;
}


/**
 * @brief Refines a bigint structure by adjusting its size and sign.
 * 
 * This function refines the given `bigint` structure by reducing its size 
 * based on the highest non-zero word and adjusting the sign if the value is zero.
 * 
 * @param[out] dst Pointer to the `bigint` structure to be refined.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_refine(OUT bigint* dst)
{
    if(dst == NULL){
        return SUCCESS;
    }

    int resize_len = dst->word_len;

    for(; resize_len > 1; resize_len --){
        if(dst->a[resize_len - 1] != 0){
            break;                  //find zero word
        }
    }
    if(dst->word_len != resize_len){
        dst->word_len = resize_len;
        dst->a = (word*)realloc(dst->a, sizeof(word)*resize_len);   //ReSize
        if(dst->a == NULL){
            fprintf(stderr, ERR_MEMORY_ALLOCATION);
        }
    }

    if((dst->word_len == 1) && (dst->a[0] == 0x00)){
        dst->sign = ZERO;
    }
    return SUCCESS;
}


/**
 * @brief Assigns the value of one bigint structure to another.
 * 
 * This function deletes the existing `bigint` structure pointed to by `dst` 
 * (if it is not NULL), creates a new `bigint` with the same word length as 
 * `src`, and copies the sign and array data from `src` to `dst`.
 * 
 * @param[out] dst Pointer to a double pointer of `bigint`, where the assigned 
 *                 bigint will be stored.
 * @param[in] src Pointer to the `bigint` structure to be copied from.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_assign(OUT bigint** dst, IN const bigint* src)
{
    if(*dst != NULL){
        bi_delete(dst);
    }
    
    bi_new(dst, src->word_len);
    (*dst)->sign = src->sign;
    array_copy(((*dst)->a), src->a, src->word_len);
    
    return SUCCESS;
}


/**
 * @brief Fills the bigint structure with zeros and resizes it.
 * 
 * This function adjusts the size of the given `bigint` structure to the specified 
 * length (`src_len`), reallocates memory for the underlying array, and fills any 
 * additional space with zeros.
 * 
 * @param[out] dst Pointer to the `bigint` structure to be modified.
 * @param[in] src_len The desired length to which the bigint should be resized.
 * @param[in] toward The direction zero padding from msb or lsb
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_fillzero(OUT bigint* dst, IN int src_len, IN int toward){

    int origin_len = dst->word_len;
    dst->word_len = src_len;
    dst->a = (word*)realloc(dst->a, sizeof(word)*src_len);
    
    if(dst->a == NULL){
        fprintf(stderr, ERR_MEMORY_ALLOCATION);
    }
    if(toward == TOP){
        while(src_len > origin_len){
            dst->a[src_len - 1] = 0;
            src_len--;
        }
    }
    else if(toward == BOTTOM){
        int diff_len = src_len - origin_len;
        while(src_len > 0){
            if(src_len > diff_len){
                dst->a[src_len - 1] = dst->a[src_len - diff_len - 1];
            }
            else{
                dst->a[src_len - 1] = 0;
            }
            src_len--;
        }
    }
    else{
        fprintf(stderr, ERR_NOT_CONDITION_FUNC);
        return FAILED;
    }
    return SUCCESS;
}


/**
 * @brief Connects two big integers like src1||src2.
 * 
 * This function connects two big intergers. 
 * the result of conneting integer's sign is same with src1's sign.
 * 
 * @param[out] dst Pointer to the `bigint` structure to be modified.
 * @param[in] src_len The desired length to which the bigint should be resized.
 * @param[in] toward The direction zero padding from msb or lsb
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_connect(OUT bigint** dst, IN bigint* src1, IN bigint* src2){
    
    int dst_len;

    if(src1 == NULL){
        if(src2 == NULL){
            fprintf(stderr, ERR_INVALID_INPUT);
            return FAILED;
        }
        else{
            bi_assign(dst, src2);
            return SUCCESS;
        }
    }
    else if(src1->sign == ZERO){
        if(src2 == NULL){
            bi_assign(dst, src1);
            return SUCCESS;
        }
        else{
            bi_assign(dst, src2);
        }
    }
    else{
        if(src2 == NULL){
            bi_assign(dst, src1);
            return SUCCESS;        
        }
    }
    
    dst_len = src1->word_len + src2->word_len;
    bi_new(dst, dst_len);

    (*dst)->sign = src1->sign;
    for(int i = 0; i < src2->word_len; i++){
        (*dst)->a[i] = src2->a[i];
    }
    for(int j = src2->word_len; j < dst_len; j++){
        (*dst)->a[j] = src1->a[j-src2->word_len];
    }
    return SUCCESS;
}


/**
 * @brief Performs a bitwise right shift on a big integer.
 * 
 * This function shifts the bits of a big integer (`dst`) to the right by a specified number of bits (`num_bits`). 
 * The resulting integer is zero-padded on the most significant bits (MSB) after the shift. The sign of the 
 * integer remains unchanged. 
 * 
 * @param[out] dst Pointer to the `bigint` structure to be modified with the shifted value.
 * @param[in] num_bits The number of bits to shift to the right.
 * @return Returns 1 on success, -1 on failure (e.g., invalid input or memory allocation error).
 */
msg bi_bit_rshift(OUT bigint* dst, IN int num_bits)
{
    int num_shift_words = 0;
    int num_shift_bits = 0;
    int dst_len = 0;
    
    if((dst == NULL) || (num_bits < 0)) 
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    if((dst->sign == ZERO) || (num_bits == 0))
    {
        return SUCCESS;
    }

    dst_len = dst->word_len;
    num_shift_words = num_bits / (sizeof(word) * 8);
    num_shift_bits = num_bits % (sizeof(word) * 8);

    if(num_shift_words >= dst_len || ((dst_len - 1 == num_shift_words) && ((dst->a[dst_len - 1]) >> num_shift_bits == 0)))
    {
#if ZERORIZE == 1
        array_init(dst->a, dst_len);
#endif
        dst->a = (word*)realloc(dst->a, sizeof(word) * 1);
        if(dst->a == NULL)
        {
            fprintf(stderr, ERR_MEMORY_ALLOCATION);
            return FAILED;
        }
        dst->sign = ZERO;
        dst->word_len = 1;
        
        return SUCCESS;
    }

    if(num_shift_words > 0)
    {
        for (int word_index = 0; word_index < dst_len - num_shift_words; word_index++)
        {
            dst->a[word_index] = dst->a[word_index + num_shift_words];
        }
#if ZERORIZE == 1
            array_init(dst->a + dst_len - num_shift_words, num_shift_words);
#endif
        dst->a = (word*)realloc(dst->a, sizeof(word) * (dst_len - num_shift_words));
        if(dst->a == NULL)
        {
            fprintf(stderr, ERR_MEMORY_ALLOCATION);
            return FAILED;
        }
        dst->word_len -= num_shift_words;

        dst_len = dst->word_len;
    }
    
    if(num_shift_bits > 0)
    {
        for (int word_index = 0; word_index < dst_len - 1; word_index++)
        {
            dst->a[word_index] >>= num_shift_bits;
            dst->a[word_index] ^= (dst->a[word_index + 1] << (sizeof(word) * 8 - num_shift_bits));
        }

        dst->a[dst_len - 1] >>= num_shift_bits;
        if(dst->a[dst_len - 1] == 0)
        {
            dst->a = (word*)realloc(dst->a, sizeof(word) * (dst_len - 1));
            if(dst->a == NULL)
            {
                fprintf(stderr, ERR_MEMORY_ALLOCATION);
                return FAILED;
            }
            dst->word_len--;
        }
    }
    
    return SUCCESS;
}


/**
 * @brief Performs a bitwise left shift on a big integer.
 * 
 * This function shifts the bits of a big integer (`dst`) to the left by a specified number of bits (`num_bits`). 
 * The resulting integer is zero-padded on the least significant bits (LSB) after the shift. The sign of the 
 * integer remains unchanged. 
 * 
 * @param[out] dst Pointer to the `bigint` structure to be modified with the shifted value.
 * @param[in] num_bits The number of bits to shift to the left.
 * @return Returns 1 on success, -1 on failure (e.g., invalid input or memory allocation error).
 */
msg bi_bit_lshift(OUT bigint* dst, IN int num_bits)
{
    int num_shift_words = 0;
    int num_shift_bits = 0;
    int dst_len = 0;
    
    if((dst == NULL) || (num_bits < 0)) 
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    if((dst->sign == ZERO) || (num_bits == 0))
    {
        return SUCCESS;
    }

    dst_len = dst->word_len;
    num_shift_words = num_bits / (sizeof(word) * 8);
    num_shift_bits = num_bits % (sizeof(word) * 8);

    if(num_shift_words > 0)
    {
        dst->a = (word*)realloc(dst->a, sizeof(word) * (dst_len + num_shift_words));
        array_init(dst->a + dst_len, num_shift_words);
        if(dst->a == NULL)
        {
            fprintf(stderr, ERR_MEMORY_ALLOCATION);
            return FAILED;
        }
        for (int word_index = dst_len - 1; word_index >= 0; word_index--)
        {
            dst->a[word_index + num_shift_words] = dst->a[word_index];
            dst->a[word_index] = 0;
        }
        dst->word_len += num_shift_words;
    }
    
    
    dst_len = dst->word_len;
    if (num_shift_bits > 0)
    {
        if(((dst->a[dst_len - 1]) >> (sizeof(word) * 8 - num_shift_bits)) != 0)
        {
            dst->a = (word*)realloc(dst->a, sizeof(word) * (dst_len + 1));
            dst->a[dst_len] = 0;
            if(dst->a == NULL)
            {
                fprintf(stderr, ERR_MEMORY_ALLOCATION);
                return FAILED;
            }
            dst->word_len++;
            dst_len++;
        }
        
        for (int word_index = dst_len - 1; word_index > 0; word_index--)
        {
            dst->a[word_index] <<= num_shift_bits;
            dst->a[word_index] ^= (dst->a[word_index - 1] >> (sizeof(word) * 8 - num_shift_bits));
        }
        dst->a[0] <<= num_shift_bits;
    }
    return SUCCESS;
}

/**
 * @brief Compares two bigint values.
 * 
 * This function compares two `bigint` structures, returning a value that indicates
 * their relative sizes. It takes into account the sign of the bigints and their
 * lengths to determine the result.
 * 
 * @param[in] A Pointer to the first `bigint` structure to be compared.
 * @param[in] B Pointer to the second `bigint` structure to be compared.
 * 
 * @return 
 *   - 1 if `A` is greater than `B`,
 *   - 0 if `A` is equal to `B`,
 *   - -1 if `A` is less than `B`.
 */
int bi_compare(IN const bigint* A, IN const bigint* B){
    
    int A_sign = A->sign;
    if (A->sign!=B->sign){
        if(A->sign == ZERO)
        {
            return (-1) * B->sign;
        }
        return A_sign;
    }
    else {
        if(A->word_len > B->word_len){
            return A_sign;
        }
        else if (A->word_len < B->word_len){
            return (-1)*A_sign;
        }
        
        else{   // if same word_len, compare 0 ~ (word_len - 1) single words
            for (int i = 1; i <= A->word_len; i++){
                if(A->a[A->word_len-i] > B->a[B->word_len-i]){
                    return A_sign;
                }
                else if(A->a[A->word_len-i] < B->a[B->word_len-i]){
                    return (-1)*A_sign;
                }
            }
            return 0;
        }
    }
}


/***********************************************
 * Greatest Common Divisor (GCD)
 ***********************************************/
/**
 * @brief Computes the greatest common divisor (GCD) of two big integers using the Euclidean algorithm.
 * 
 * This function calculates the GCD of the input integers `src1` and `src2`. It uses the classical 
 * Euclidean algorithm, which iteratively computes the remainder until the remainder becomes zero.
 * The last non-zero remainder is the GCD.
 * 
 * @param[out] gcd Pointer to the bigint that will hold the greatest common divisor of `src1` and `src2`.
 * @param[in] src1 The first bigint for the GCD computation.
 * @param[in] src2 The second bigint for the GCD computation.
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid input or memory allocation error).
 */
msg bi_gcd(OUT bigint** gcd, IN const bigint* src1, IN const bigint* src2)
{
    if((src1 == NULL) || (src2 == NULL) || (src1->a == NULL) || (src2->a == NULL) || (src1->word_len <= 0) 
    || (src2->word_len <= 0) || (src1->sign != POSITIVE) || (src2->sign != POSITIVE))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* t2 = NULL;
    bigint* quotient = NULL;
    bigint* buf = NULL;

    bi_assign(&t0, src1);
    bi_assign(&t1, src2);
    while (t1->sign != ZERO)
    {
        bi_assign(&t2, t0);
        bi_assign(&t0, t1);
        bi_word_division(&quotient, &buf, t2, t1);
        bi_assign(&t1, buf);
    }

    bi_assign(gcd, t0);
    bi_delete(&t0);
    bi_delete(&t1);
    bi_delete(&t2);
    bi_delete(&quotient);
    bi_delete(&buf);

    return SUCCESS;
}


/***********************************************
 * Extended Euclidean Algorithm (EEA)
 ***********************************************/
/**
 * @brief Computes the greatest common divisor (GCD) of two big integers and finds their Bézout coefficients.
 * 
 * This function performs the Extended Euclidean Algorithm on the input integers `src1` and `src2` to calculate:
 * - The greatest common divisor (`gcd`)
 * - Bézout coefficients (`x` and `y`) such that `src1 * x + src2 * y = gcd(src1, src2)`
 * 
 * It is useful for applications such as modular inverses in cryptographic algorithms.
 * 
 * @param[out] gcd Pointer to the bigint that will hold the greatest common divisor of `src1` and `src2`.
 * @param[out] x Pointer to the bigint that will hold the Bézout coefficient for `src1`.
 * @param[out] y Pointer to the bigint that will hold the Bézout coefficient for `src2`.
 * @param[in] src1 The first bigint for the GCD computation.
 * @param[in] src2 The second bigint for the GCD computation.
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid input or memory allocation error).
 */
msg bi_EEA(OUT bigint** gcd, OUT bigint** x, OUT bigint** y, IN const bigint* src1, IN const bigint* src2)
{
    if((src1 == NULL) || (src2 == NULL) || (src1->a == NULL) || (src2->a == NULL) || (src1->word_len <= 0) 
    || (src2->word_len <= 0) || (src1->sign != POSITIVE) || (src2->sign != POSITIVE))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* u0 = NULL;
    bigint* v0 = NULL;
    bigint* u1 = NULL;
    bigint* v1 = NULL;
    bigint* u2 = NULL;
    bigint* v2 = NULL;
    bigint* quotient = NULL;
    bigint* remainder = NULL;
    bigint* buf = NULL;

    bi_new(&buf, 1);
    buf->sign = POSITIVE;
    buf->a[0] = 1;

    // (t0, t1) <- (a, b)
    bi_assign(&t0, src1);
    bi_assign(&t1, src2);

    // (u0, v0) <- (1, 0)
    bi_assign(&u0, buf);
    bi_new(&v0, 1);

    // (u1, v1) <- (0, 1)
    bi_new(&u1, 1);
    bi_assign(&v1, buf);

    while(t1->sign != ZERO)
    {
        // (q, r) <- div(t0, t1)
        bi_word_division(&quotient, &remainder, t0, t1);

        // (t0, t1) <- (t1, r)
        bi_assign(&t0, t1);
        bi_assign(&t1, remainder);

        // (u2, v2) <- (u0 - qu1, v0 -qv1)
        bi_mul_kara(&buf, quotient, u1);
        bi_sub(&u2, u0, buf);
        bi_mul_kara(&buf, quotient, v1);
        bi_sub(&v2, v0, buf);

        // (u0, v0) <- (u1, v1)
        bi_assign(&u0, u1);
        bi_assign(&v0, v1);

        // (u1, v1) <- (u2, v2)
        bi_assign(&u1, u2);
        bi_assign(&v1, v2);
        
    }

    //return
    bi_assign(gcd, t0);
    bi_assign(x, u0);
    bi_assign(y, v0);

    bi_delete(&t0);
    bi_delete(&t1);
    bi_delete(&u0);
    bi_delete(&v0);
    bi_delete(&u1);
    bi_delete(&v1);
    bi_delete(&u2);
    bi_delete(&v2);
    bi_delete(&quotient);
    bi_delete(&remainder);
    bi_delete(&buf);

    return SUCCESS;
}