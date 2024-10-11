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

// 포인터로 하지않으면 구조체가 다 복사되서 넘어가기 때문에 메모리적으로 포인터가 더효율적
// 현재는 16진수와 2진수 출력만 하기
msg bi_print(bigint** dst, int base)
{
    if(base == 2)
    {
        if((*dst)->sign == POSITIVE)
        {
            printf("0b");
        }
        else if((*dst)->sign == NEGATIVE)
        {
            printf("-0b");
        }
        else
        {
            return FAILED;
        }
        for(int word_index = (*dst)->word_len ; word_index > 0 ; word_index--)
        {
            for(int bit_index = 8 * sizeof(word) - 1; bit_index >=0 ; bit_index--)
            {
                printf("%1u", (((*dst)->a[word_index]) >> bit_index) & (0x01));
            }
        }
        return SUCCESS;
    }
    else if(base = 16)
    {
        if((*dst)->sign == POSITIVE)
        {
            printf("0x");
        }
        else if((*dst)->sign == NEGATIVE)
        {
            printf("0x");
        }
        else
        {
            return FAILED;
        }
        for(int word_index = (*dst)->word_len; word_index > 0; word_index--)
        {
            printf("%04x", (*dst)->a[word_index - 1]);
        }

        return SUCCESS;
    }
    return FAILED;
}

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

    (*dst) -> sign = 0;
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

void array_init(word* a, int word_len)
{
    for(int word_index = 0; word_index<word_len; word_index++)
    {
        a[word_index] = 0;
    }
}

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

msg bi_refine(bigint** dst)
{
    if(dst == NULL){    //x가 비어있으면 반환
        return 0;
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

    if((dst->word_len == 1) && (dst->a[0] == 0x00)){    //만약 0이면 sign -> NON_NEGATIVE
        dst->sign = NON_NEGATIVE;
    }
    return 0;
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
    
    return 0;
}