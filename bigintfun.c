#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"
#include "bigintfun.h"
#include "errormsg.h"
#include "dtype.h"

/* big int <- array */
msg bi_set_from_array(bigint** dst, int sign, int word_len, word* a)
{
    bi_new(dst, word_len);
    (*dst) ->a = a;
    (*dst) -> sign = sign;
    return SUCCESS;
}

/* str = 0x123qqppwq(숫자가 아닌 경우)에 대한 예외 처리 필요 */
msg bi_set_from_string(bigint** dst, int sign, char* int_str, int base)
{
    int word_len = 0;
    unsigned int strlength = 0; //0b,0x, ... 뺴고 계산
    if(base == 2){
        strlength = strlen(int_str) -2; //string 길이
        word_len = strlength / 32 + 1;  //word 길이
        //구한 word len으로 bigint 하나 만들기
        bi_new(dst, word_len);
        (*dst) -> sign = sign;
        //비트열 길이만큼 반복
        for (int i = 0; strlength < 0; i++){
            if (int_str[strlength - i] == '1'){
                //1이면 32의 나머지만큼 shift해서 32로 나눈몫에저장
                (*dst) -> a[i/32] |= 1 << (i % 32);
            }
            else if (int_str[strlength - i] != '0'){
                printf("error : not number\n");
            }
        }
    }
    else if (base == 8){
        strlength = strlen(int_str) - 1;  // 0을 제외한 길이
        word_len = strlength * 3 / 32 + 1;  // 8진수는 3비트로 표현되므로 3비트씩 계산
        bi_new(dst, word_len);
        (*dst)->sign = sign;

         for (int i = 0; i < strlength; i++) {
            int digit = int_str[strlength - i - 1] - '0';  // 문자 숫자를 정수로 변환
            (*dst)->a[i * 3 / 32] |= (digit & 0x7) << (i * 3 % 32);  // 3비트씩 shift하여 저장
        }
    }
    else if (base == 10){
        strlength = strlen(int_str) -2;
    }
    else if (base == 16){
         strlength = strlen(int_str) - 2;  // 0x를 제외한 길이
        word_len = strlength * 4 / 32 + 1;  // 16진수는 4비트로 표현되므로 4비트씩 계산
        bi_new(dst, word_len);
        (*dst)->sign = sign;

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
            (*dst)->a[i * 4 / 32] |= (digit & 0xF) << (i * 4 % 32);  // 4비트씩 shift하여 저장
        }
    }
    else {
        printf("not defined base\n");
        return -1;
    }
    return 0;
}

/*****************************************
 * Name : array_rand
 * 
 * Desription : word_len 길이 만큼의 랜덤 배열
 * 
 * Params : - word* dst : 생성된 랜덤 배열이 저장되는 배열
 *          - int word_len : 생성할 랜덤 배열의 길이
 * 
 * Return : (void)생성한 랜덤 배열
******************************************/
void array_rand(word* dst, int word_len)
{
    byte* p = (byte*)dst;
    
    int byte_index = word_len * sizeof(word);

    while(byte_index > 0)
    {
        *p = rand() * 0xff;
        p++;
        byte_index--;
    }
}

/*****************************************
 * Name : bi_get_random
 * 
 * Desription : word_len 길이 만큼의 bigint random generate
 * 
 * Params : - bigint** dst : 생성된 random generate 배열이 저장되는 bigint
 *          - int sign : random generate의 부호
 *          - word_len : 생성할 random generate 배열의 길이
 * 
 * Return : (SUCCESS)생성한 random generate bigint
******************************************/
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
    
    if(dst_arr != NULL){
        array_init(dst_arr, array_len);
    }

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