#include <stdio.h>


#include "operation.h"
#include "bigintfun.h"
#include "params.h"
#include "errormsg.h"

//single word A + B + carry
word add_c(word src1, word src2, int* c){
    word result = src1 + src2;
    int cout = 0;
    if (result < src1){
        cout = 1;
    }
    result += *c;
    if(result < *c){
        cout += 1;
    }
    *c = cout;
    return result;
}

//src1 >= src2
msg add_same_sign(bigint** dst, bigint* src1, bigint* src2){
    int max_len;
    int c = 0;
    word result;
    max_len = src1->word_len;
    bi_new(dst, max_len + 1);   //더 긴 길이의 bigint만큼 생성

    if((src1->sign) == (src2->sign)){
        if(src1->sign == POSITIVE){
            (*dst)->sign = POSITIVE;
        }
        else{
            (*dst)->sign = NEGATIVE;
        }
    }
    else{
        fprintf(stderr, ERR_NOT_CONDITION_FUNC);
    }
    
    if((src1->word_len) > (src2->word_len)){
        bi_fillzero(&src2, src1->word_len);
    }
    for(int idx = 0; idx < max_len; idx++){    
        result = add_c(src1->a[idx], src2->a[idx], &c);
        (*dst)->a[idx] = result;
    }
    if(c == 1){
        (*dst)->a[max_len] = 1;        //마지막 carry가 1이면 src1 크기를 넘어간다.
    }
    else{
        bi_refine(*dst);             //마지막 carry가 0이면 크기 조절 후 마무리
    }
    return SUCCESS;
}

// msg bi_add(bigint *dst, bigint* src1, bigint* src2){
//     word temp = 0;
//     word temp1 = 0;
//     for(int idx = 0; idx < src1->word_len; idx++){
//         temp |= src1->a[idx];
//     }
//     for(int idx = 0; idx < src2->word_len; idx++){
//         temp1 |= src2->a[idx];
//     }

//     if(temp == 0){
//         bi_assign(&dst, src2);
//         return SUCCESS;
//     }
//     if(temp1 == 0){
//         bi_assign(&dst, src1);
//         return SUCCESS;
//     }

//     if((src1->sign == POSITIVE) && (src2->sign == NEGATIVE)){
//         src2->sign = POSITIVE;
//         bi_sub(&dst, src1, src2);
//         return SUCCESS;
//     }
//     if((src1->sign ==  NEGATIVE) && (src2->sign ==  POSITIVE)){
//         src1->sign = POSITIVE;
//         bi_sub(&dst, src2, src1);
//         return SUCCESS;
//     }

//     if ((bi_compare(src1, src2) == 1) || (bi_compare(src1, src2) == 0)){
//         add_same_sign(dst, src1, src2);
//         return SUCCESS;
//     }
//     else{     //A < B
//         add_same_sign(dst, src2, src1);
//         return SUCCESS;
//     }
// }
