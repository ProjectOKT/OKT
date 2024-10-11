#include <stdio.h>
#include <stdlib.h>
#include "bigintfun.h"

/* big int <- array */
msg bi_set_from_array(bigint** dst, int sign, int word_len, word* a)
{
    return 0;
}

/* str = 0x123qqppwq(숫자가 아닌 경우)에 대한 예외 처리 필요 */
msg bi_set_from_string(bigint** dst, char* int_str, int base)
{
    return 0;
}

/* A[4] = {1,2,3,0} -> {1.2.3.*1*} */
// 마지막 배열은 nonzero라는 보장이 필요 word_len을 맞추기 위해
msg bi_get_random(bigint** dst, int word_len)
{
    return 0;
}

// 포인터로 하지않으면 구조체가 다 복사되서 넘어가기 때문에 메모리적으로 포인터가 더효율적
// 현재는 16진수와 2진수 출력만 하기
msg bi_print(bigint** dst, int base)
{
    return 0;
}

msg bi_new(bigint** dst, int word_len)
{
    if(*dst != NULL)
    {
        printf("bi_new func dst not empty\n");
        bi_delete(dst);
    }
    
    (*dst) = (bigint*)calloc(1, sizeof(bigint));
    if((*dst) == NULL)
    {
        printf("bi_new func dst alloc fail\n");
        return -1;
    }

    (*dst) -> sign = 0;
    (*dst) -> word_len = word_len;
    (*dst) -> a = (word*)calloc(word_len, sizeof(word));

    if((*dst) -> a == NULL)
    {
        printf("bi_new func array alloc fail\n");
        bi_delete(dst);
        return -1;
    }

    return 0;
}

msg bi_delete(bigint** dst)
{
    if((*dst) == NULL)
    {
        return 1;
    }
    return 0;
}


msg bi_refine(bigint** dst)
{
    return 0;
}

/* tmp <- x */
msg bi_assign(bigint** dst, bigint** src)
{
    return 0;
}