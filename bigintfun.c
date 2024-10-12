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

/*****************************************
 * Name : bi_print
 * 
 * Desription : bigint를 입력받아 2진수 혹은 16진수 출력
 * 
 * Params : - bigint** dst : print하려는 bigint
 *          - int base : 진수변환 base
 * 
 * Return : (SUCCESS)진수변환된 bigint print
******************************************/
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

/*****************************************
 * Name : bi_new
 * 
 * Desription : word_len만큼의 배열크기를 가지는 bigint를 만들어줌
 * 
 * Params : - bigint** dst : 생성하려는 bigint
 *          - int word_len : word array 길이
 * 
 * Return : (SUCCESS)new bigint
******************************************/
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

/*****************************************
 * Name : array_init
 * 
 * Desription : 배열을 word_len만큼 0으로 초기화
 * 
 * Params : - word* a : 초기화하려는 array
 *          - int word_len : word array 길이
 * 
 * Return : zero inited array
******************************************/
void array_init(word* a, int word_len)
{
    for(int word_index = 0; word_index<word_len; word_index++)
    {
        a[word_index] = 0;
    }
}

/*****************************************
 * Name : bi_delete
 * 
 * Desription : bigint를 입력받아 동작할당 받은 공간을 반환
 *              (ZERORIZE가 1일시에 할당되었던 배열 메모리에 0으로 초기화 하고 반환)
 * 
 * Params : - bigint** dst : 반환(삭제)하려는 bigint
 * 
 * Return : (SUCCESS) NULL dst
******************************************/
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

/*****************************************
 * Name : bi_refine
 * 
 * Desription : bigint dst의 last zero들을 삭제 후 재정의
 * 
 * Params : - bigint* dst : 길이를 조절하려는 bigint
 * 
 * Return : (Resized) dst
******************************************/
msg bi_refine(bigint* dst)
{
    if(dst == NULL){    //x가 비어있으면 반환
        return SUCCESS;
    }

    int resize_len = dst->word_len;

    for(int idx = resize_len; idx > 1; idx --){
        if(dst->a[idx - 1] != 0){
            break;                  //기존 배열의 상위 인덱스부터 0이 아닐 때까지 size down
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

/*****************************************
 * Name : array_copy
 * 
 * Desription : src array를 dst array로 copy
 * 
 * Params : - bigint* dst_arr : 복사하려는 dst 배열
 *          - bigint* src_arr : 복사받으려는 src 배열
 *          - int array_len : 복사하려는 길이
 * 
 * Return : copied dst array
******************************************/
void array_copy(word* src_arr, word* dst_arr, int array_len)
{
    for(int index = 0; index < array_len; index++)
    {
        dst_arr[index] = src_arr[index];
    }
}

/*****************************************
 * Name : bi_assign
 * 
 * Desription : bigint src를 bigint dst로 copy
 * 
 * Params : - bigint* dst : 복사하려는 dst 배열
 *          - bigint* src : 복사받으려는 src 배열
 * 
 * Return : (SUCCESS) copied bigint dst
******************************************/
msg bi_assign(bigint** dst, bigint* src)
{
    if(*dst != NULL){
        bi_delete(dst);
    }
    
    bi_new(dst, src->word_len);     //src의 길이만큼 생성
    (*dst)->sign = src->sign;   //부호 복사
    array_copy(((*dst)->a), src->a, src->word_len);
    
    return SUCCESS;
}