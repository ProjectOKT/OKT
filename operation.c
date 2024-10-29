#include <stdio.h>


#include "operation.h"
#include "bigintfun.h"
#include "params.h"

msg bi_add_same_sign(bigint** dst, bigint* src1, bigint* src2){
    //더 큰 수 비교
    if (bi_compare(&src1, &src2) == POSITIVE){
        int max_len = src1->word_len;
        for(int idx = 0; idx < max_len; idx){
            
        }
    }
}

/*****************************************
 * Name : bi_compare
 * 
 * Desription : 두 가지 bigint를 입력받아 2진수 혹은 16진수 출력
 * 
 * Params : - bigint** a : bigint a
 *          - bigint** b : bigint b
 * 
 * Return : a > b return 1, a = b return 0, a < b return -1
******************************************/
msg bi_compare(bigint** A, bigint** B){
    //부호가 다를 때
    int A_sign = (*A)->sign;
    if ((*A)->sign!=(*B)->sign){
        return A_sign;
    }
    //부호가 같을 때
    else {
        // A의 길이가 더 클 때
        if((*A)->word_len > (*B)->word_len){
            return A_sign;
        }
        // B의 길이가 더 클 때
        else if ((*A)->word_len < (*B)->word_len){
            return (-1)*A_sign;
        }
        // 길이가 같을 때 제일 마지막 배열인자 비교
        else{
            //A가 더 클 때
            if((*A)->a[(*A)->word_len-1] > (*B)->a[(*B)->word_len-1]){
                return A_sign;
            }
            //B가 더 클 때
            else if((*A)->a[(*A)->word_len-1] < (*B)->a[(*B)->word_len-1]){
                return (-1)*A_sign;
            }
            else{
                return 0;
            }
        }
    }
}