/*
    2024.10.22
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ZERORIZE

typedef uint32_t msg;
// typedef unsigned int word;
// 컴퓨터 마다 unsigned int의 크기가 다를수 있기 때문에 uint32_t를 사용
// c99 이상 사용가능
typedef uint32_t word;

typedef struct {
    int sign;
    int word_len;
    word* a;
} bigint;

/* big int <- array */
msg bi_set_from_array(bigint** dst, int sign, int word_len, word* a);

/* str = 0x123qqppwq(숫자가 아닌 경우)에 대한 예외 처리 필요 */
msg bi_set_from_string(bigint** dst, char* int_str, int base);

/* A[4] = {1,2,3,0} -> {1.2.3.*1*} */
// 마지막 배열은 nonzero라는 보장이 필요 word_len을 맞추기 위해
msg bi_get_random(bigint** dst, int word_len);

// 포인터로 하지않으면 구조체가 다 복사되서 넘어가기 때문에 메모리적으로 포인터가 더효율적
msg bi_print(bigint** dst, int base); // 현재는 16진수와 2진수 출력만 하기

msg bi_new(bigint** dst, int word_len);
msg bi_delete(bigint** dst); // 반납시에 비밀값은 0으로 씌우고 지워야함

msg bi_refine(bigint** dst);

/* tmp <- x */
msg bi_assign(bigint** dst, bigint** src);

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
        printf('bi_new func array alloc fail\n');
        bi_delete(dst);
        return -1;
    }
}

msg bi_delete(bigint** dst)
{
    if((*dst) == NULL)
    {
        return 1;
    }
}


int main()
{
    //puts("Hello, KMU!");
    
    bigint a, b, c;
    /*
        a = -0x1231231414124124
        b = 0x1231231414124124
        a = b // a에 어떤값이 들어있는지 중요
    */

    bi_set_from_string(&a, '-0x1231231414124124', 16);
    bi_set_from_string(&b, '0x1231231414124124', 16);
    bi_assign(&a, &b);


    return 0;
}