#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "bigintfun.h"
#include "errormsg.h"
#include "dtype.h"

/* big int <- array */
msg bi_set_from_array(bigint** dst, int sign, int word_len, word* a)
{
    return SUCCESS;
}

/* str = 0x123qqppwq(숫자가 아닌 경우)에 대한 예외 처리 필요 */
msg bi_set_from_string(bigint** dst, char* int_str, int base)
{
    return SUCCESS;
}

/* A[4] = {1,2,3,0} -> {1.2.3.*1*} */
// 마지막 배열은 nonzero라는 보장이 필요 word_len을 맞추기 위해
msg bi_get_random(bigint** dst, int word_len)
{
    return SUCCESS;
}

/*
* bi_print: bigint를 입력받아 2진수 혹은 16진수 출력
*
* param dst: bigint의 2중 포인터
* param base: 2진수 혹은 16진수 입력
* return: error code
*/
msg bi_print(bigint** dst, int base)
{
    if((*dst)->sign == ZERO) // sign ZERO면 ZERO출력 후 반환
    {
        printf("ZERO");
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

/*
* bi_new: word_len만큼의 배열크기를 가지는 bigint를 만들어줌
*
* param dst: bigint의 2중 포인터
* param word_len: 배열 크기
* return: error code
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

/*
* array_init: 배열을 word_len만큼 0으로 초기화
*
* param a: 초기화 하고자하는 배열
* param word_len: 배열 크기
* return: void
*/
void array_init(word* a, int word_len)
{
    for(int word_index = 0; word_index<word_len; word_index++)
    {
        a[word_index] = 0;
    }
}

/*
* bi_delete: bigint를 입력받아 동작할당 받은 공간을 반환(ZERORIZE가 1일시에 할당되었던 배열 메모리에 0으로 초기화 하고 반환)
*
* param dst: 초기화 bigint
* return: error_code
*/
msg bi_delete(bigint** dst)
{
    if((*dst) == NULL)
    {
        return SUCCESS;
    }
#if ZERORIZE == 1
    array_init((*dst)->a, (*dst)->word_len);
#endif
    free((*dst)->a);
    free((*dst));
    (*dst) = NULL;

    return SUCCESS;
}

msg bi_refine(bigint* dst)
{
    if(dst == NULL){    //x가 비어있으면 반환
        return SUCCESS;
    }

    int resize_len = dst->word_len;

    for(int idx = resize_len; idx > 1; idx --){
        if(dst->a[idx - 1] != 0){
            break;                  //기존 msb부터 1이면 stop 0이면 down size
        }
    }
    if(dst->word_len != resize_len){        //기존 길이에서 resize 됐다면,
        dst->word_len = resize_len;
        dst->a = (word*)realloc(dst->a, sizeof(word)*resize_len);   //변환길이만큼 재할당
    }

    if((dst->word_len == 1) && (dst->a[0] == 0x00)){    //만약 0이면 sign -> ZERO
        dst->sign = ZERO;
    }
    return SUCCESS;
}

void array_copy(word* a, word* b, int array_len)
{
    for(int index = 0; index <array_len;index++)
    {
        b[index] = a[index];
    }
}

/* tmp <- x */
msg bi_assign(bigint** dst, bigint* src)
{
    if(*dst != NULL){
        bi_delete(dst);
    }
    
    bi_new(dst, src->word_len);     //src의 길이만큼 생성
    (*dst)->sign = src->sign;   //부호 복사
    array_copy(((*dst)->a), src->a, src->word_len);     //array_copy 만들어야함(Oct_11)
    
    return SUCCESS;
}