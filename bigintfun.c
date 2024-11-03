#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"
#include "bigintfun.h"
#include "errormsg.h"
#include "dtype.h"
#include "arrayfun.h"

/**
 * @brief Convert an array to a bigint.
 *
 * @description This function takes an array as input and converts it to a bigint.
 *
 * @param[out] dst Pointer to the bigint where the converted value will be stored.
 * @param[in] sign The sign of the bigint to be created.
 * @param[in] word_len The length of the array to be converted.
 * @param[in] a Pointer to the array to be converted to bigint.
 *
 * @return (SUCCESS) The converted bigint.
 */
msg bi_set_from_array(bigint** dst, int sign, int word_len, const word* a)
{
    bi_new(dst, word_len);
    for (int i = 0; i < word_len; i++){
        (*dst) -> a[i] = a[i];
    }
    (*dst) -> sign = sign;

    return SUCCESS;
}

/**
 * @brief Convert a string to a bigint considering the specified base.
 *
 * @description This function takes a string input and converts it to a bigint, 
 * taking into account the specified base and the sign of the string.
 *
 * @param[out] dst Pointer to the bigint where the converted value will be stored.
 * @param[in] base The base for conversion.
 * @param[in] sign The sign of the string to be converted.
 * @param[in] int_str The string to be converted to bigint.
 *
 * @return (SUCCESS) The converted bigint.
 */
msg bi_set_from_string(bigint** dst, const char* int_str, int base)
{
    int word_len = 0;
    unsigned int strlength = 0; 
    if (base == 2){
        if (int_str[0] == '-'){
            strlength = strlen(int_str) - 1; //string 숫자 길이
            word_len = strlength % SIZEOFWORD == 0 ? strlength / SIZEOFWORD : strlength / SIZEOFWORD +1;  //word 길이
            //구한 word len으로 bigint 하나 만들기
            bi_new(dst, word_len);
            (*dst) -> sign = NEGATIVE;
            for (int i = 0; i < strlength; i++){
                if (int_str[strlength - i] == '1'){
                    //1이면 32의 나머지만큼 shift해서 64로 나눈몫에저장
                    (*dst) -> a[i/SIZEOFWORD] |= 1 << (i % SIZEOFWORD);
                }
                else if (int_str[strlength - i] != '0'){
                    fprintf(stderr, ERR_INVALID_INPUT);
                    bi_delete(dst);
                    return FAILED;
                }
            }
        }
        else{
            strlength = strlen(int_str); //string 숫자 길이
            word_len = strlength % SIZEOFWORD == 0 ? strlength / SIZEOFWORD : strlength / SIZEOFWORD +1;  //word 길이
            //구한 word len으로 bigint 하나 만들기
            bi_new(dst, word_len);
            (*dst) -> sign = POSITIVE;
            for (int i = 0; i < strlength; i++){
                if (int_str[strlength - i - 1] == '1'){
                    //1이면 SIZEOFWORD의 나머지만큼 shift해서 SIZEOFWORD로 나눈몫에저장
                    (*dst) -> a[i/SIZEOFWORD] |= 1 << (i % SIZEOFWORD);
                }
                else if (int_str[strlength - i - 1] != '0'){
                    fprintf(stderr, ERR_INVALID_INPUT);
                    bi_delete(dst);
                    return FAILED;
                }
            }
        }
        
    }
    else if (base == 10){
        return 0;
    }
    else if (base == 16){
        if (int_str[0] == '-'){
            strlength = strlen(int_str)-1;  // 0x를 제외한 길이
            word_len = strlength * 4 % SIZEOFWORD == 0 ? strlength * 4 / SIZEOFWORD : strlength * 4 / SIZEOFWORD +1;  
            bi_new(dst, word_len);
            (*dst)->sign = NEGATIVE;
            for (int i = 0; i < strlength; i++) {
                char c = int_str[strlength - i];
                int digit = 0;

                // 16진수 문자를 정수로 변환
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
                (*dst)->a[i * 4 / SIZEOFWORD] |= (digit & 0xF) << (i * 4 % SIZEOFWORD);  // 4비트씩 shift하여 저장
            }
        }
        else {
            strlength = strlen(int_str); 
            word_len = strlength * 4 % SIZEOFWORD == 0 ? strlength * 4 / SIZEOFWORD : strlength * 4 / SIZEOFWORD +1;  
            bi_new(dst, word_len);
            (*dst)->sign = POSITIVE;
            for (int i = 0; i < strlength; i++) {
                char c = int_str[strlength - i - 1];
                int digit = 0;

                // 16진수 문자를 정수로 변환
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
                (*dst)->a[i * 4 / SIZEOFWORD] |= (digit & 0xF) << (i * 4 % SIZEOFWORD);  // 4비트씩 shift하여 저장
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
 * @brief Generate a random bigint of specified word length.
 *
 * @description This function generates a random bigint with a length defined by word_len.
 *
 * @param[out] dst Pointer to the bigint where the generated random value will be stored.
 * @param[in] sign The sign of the random number to be generated.
 * @param[in] word_len The length of the random bigint array to be created.
 *
 * @return (SUCCESS) The generated random bigint.
 */
msg bi_get_random(bigint** dst, int sign, int word_len)
{
    msg err_code = 0;
    err_code = bi_new(dst, word_len);
    if (err_code == FAILED)
    {
        return FAILED;
    }

    (*dst) -> sign = sign;
    
    while(!((*dst)->a[word_len - 1])) // 마지막 배열 Nonzero 보장
    {
        array_rand((*dst)->a, word_len);
    }

    return SUCCESS;
}

/**
 * @brief Print a bigint in binary or hexadecimal format.
 *
 * @description This function takes a bigint as input and outputs it in either binary or hexadecimal format, 
 * depending on the specified base.
 *
 * @param[in] dst Pointer to the bigint to be printed.
 * @param[in] base The base for conversion (e.g., 2 for binary, 16 for hexadecimal).
 *
 * @return (SUCCESS) The bigint printed in the specified base.
 */
msg bi_print(bigint** dst, int base)
{
    if((*dst)->sign == ZERO) // sign ZERO면 ZERO출력 후 반환
    {
        printf("ZERO\n");
        return SUCCESS;
    }

    if(base == 2) // 2진수
    {
        if((*dst)->sign == POSITIVE) // 양수 음수 출력
        {
            printf("0b");
        }
        else if((*dst)->sign == NEGATIVE)
        {
            printf("-0b");
        }
        else
        {
            return FAILED; // sign 값이 -1, 0, 1이 아니라면 에러코드
        }
        for(int word_index = (*dst)->word_len ; word_index > 0 ; word_index--)
        {
            for(int bit_index = 8 * sizeof(word) - 1; bit_index >=0 ; bit_index--)
            {
                printf("%1u", (((*dst)->a[word_index - 1]) >> bit_index) & (0x01));
            }
        }
        printf("\n");

        return SUCCESS;
    }
    else if(base == 16) // 16진수
    {
        if((*dst)->sign == POSITIVE) // 양수 음수 출력
        {
            printf("0x");
        }
        else if((*dst)->sign == NEGATIVE)
        {
            printf("-0x");
        }
        else
        {
            fprintf(stderr, ERR_INVALID_INPUT);
            return FAILED; // sign 값이 -1, 0, 1이 아니라면 에러코드
        }
        for(int word_index = (*dst)->word_len; word_index > 0; word_index--)
        {
            printf("%08x", (*dst)->a[word_index - 1]);
        }
        printf("\n");

        return SUCCESS;
    }

    return FAILED; // 2, 16이외의 base값은 에러코드
}

/**
 * @brief Print a bigint in binary or hexadecimal format.
 *
 * @description This function takes a bigint as input and outputs it in either binary or hexadecimal format, 
 * depending on the specified base.
 *
 * @param[in] file File pointer
 * @param[in] dst Pointer to the bigint to be printed.
 *
 * @return (SUCCESS) The bigint printed in the specified base.
 */
msg bi_fprint(FILE* file, bigint** dst)
{
    if((*dst)->sign == ZERO) // sign ZERO면 ZERO출력 후 반환
    {
        printf("0x0\n");
        return SUCCESS;
    }
    else if((*dst)->sign == POSITIVE) // 양수 음수 출력
    {
        printf("0x");
    }
    else if((*dst)->sign == NEGATIVE)
    {
        printf("-0x");
    }
    else
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED; // sign 값이 -1, 0, 1이 아니라면 에러코드
    }
    for(int word_index = (*dst)->word_len; word_index > 0; word_index--)
    {
        printf("%08x", (*dst)->a[word_index - 1]);
    }
    printf("\n");

    return SUCCESS;
}

/**
 * @brief Create a bigint with a specified array size.
 *
 * @description This function allocates memory for a bigint with a size determined by word_len.
 *
 * @param[out] dst Pointer to the bigint to be created.
 * @param[in] word_len The length of the word array for the bigint.
 *
 * @return (SUCCESS) A new bigint.
 */
msg bi_new(bigint** dst, int word_len)
{
    if(*dst != NULL)
    {
        fprintf(stderr, ERR_NULL_POINTER);
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
 * @brief Free the allocated memory for a bigint.
 *
 * @description This function takes a bigint and returns the allocated memory.
 *              If ZERORIZE is set to 1, the allocated array memory is initialized to 0 before being freed.
 *
 * @param[in,out] dst Pointer to the bigint to be deleted (set to NULL after deletion).
 *
 * @return (SUCCESS) NULL dst after deletion.
 */
msg bi_delete(bigint** dst)
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
 * @brief Refine a bigint by removing trailing zeros and redefining it.
 *
 * @description This function removes the last zeros from the bigint dst and resizes it.
 *
 * @param[in,out] dst Pointer to the bigint whose length will be adjusted.
 *
 * @return (Resized) The resized bigint dst.
 */
msg bi_refine(bigint* dst)
{
    if(dst == NULL){    //x가 비어있으면 반환
        return SUCCESS;
    }

    int resize_len = dst->word_len;

    for(; resize_len > 1; resize_len --){
        if(dst->a[resize_len - 1] != 0){
            break;                  //기존 배열의 상위 인덱스부터 0이 아닐 때까지 size down
        }
    }
    if(dst->word_len != resize_len){        //기존 길이에서 resize 됐다면,
        dst->word_len = resize_len;
        dst->a = (word*)realloc(dst->a, sizeof(word)*resize_len);   //변환길이만큼 재할당
        if(dst->a == NULL){
            fprintf(stderr, ERR_MEMORY_ALLOCATION);
        }
    }

    if((dst->word_len == 1) && (dst->a[0] == 0x00)){    //만약 0이면 sign -> ZERO
        dst->sign = ZERO;
    }
    return SUCCESS;
}

/**
 * @brief Copy a bigint from src to dst.
 *
 * @description This function copies the bigint array from src to dst.
 *
 * @param[out] dst Pointer to the destination bigint array to copy into.
 * @param[in] src Pointer to the source bigint array to copy from.
 *
 * @return (SUCCESS) if the copy was successful.
 */
msg bi_assign(bigint** dst, const bigint* src)
{
    if(*dst != NULL){
        bi_delete(dst);
    }
    
    bi_new(dst, src->word_len);     //src의 길이만큼 생성
    (*dst)->sign = src->sign;   //부호 복사
    array_copy(((*dst)->a), src->a, src->word_len);
    
    return SUCCESS;
}

/**
 * @brief Resizing and fill zero dst to src 
 *
 * @description This function resizing dst to src and fill zero
 *
 * @param[out] dst Pointer to the destination bigint resized
 * @param[in] src_len source size for resizing
 *
 * @return (SUCCESS) if resize and fill zero was successful.
 */
msg bi_fillzero(bigint** dst, int src_len){

    int origin_len = (*dst)->word_len;
    (*dst)->word_len = src_len;
    (*dst)->a = (word*)realloc((*dst)->a, sizeof(word)*src_len);
    
    if((*dst)->a == NULL){
        fprintf(stderr, ERR_MEMORY_ALLOCATION);
    }

    while(src_len > origin_len){
        (*dst)->a[src_len - 1] = 0;
        src_len--;
    }
    return SUCCESS;
}