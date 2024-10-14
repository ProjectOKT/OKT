#include <stdio.h>
#include <stdlib.h>

#include "arrayfun.h"
#include "params.h"
#include "dtype.h"
#include "errormsg.h"


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
        *p = rand() & 0xff;
        p++;
        byte_index--;
    }
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