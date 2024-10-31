#include <stdio.h>


#include "operation.h"
#include "bigintfun.h"
#include "params.h"
#include "errormsg.h"


/*****************************************
 * Name : bi_compare
 * 
 * Desription : 두 가지 bigint를 입력받아 2진수 혹은 16진수 출력
 * 
 * Params : - bigint* a : bigint a
 *          - bigint* b : bigint b
 * 
 * Return : a > b return 1, a = b return 0, a < b return -1
******************************************/
msg bi_compare(const bigint* A, const bigint* B){
    //부호가 다를 때
    int A_sign = A->sign;
    if (A->sign!=B->sign){
        return A_sign;
    }
    //부호가 같을 때
    else {
        // A의 길이가 더 클 때
        if(A->word_len > B->word_len){
            return A_sign;
        }
        // B의 길이가 더 클 때
        else if (A->word_len < B->word_len){
            return (-1)*A_sign;
        }
        // 길이가 같을 때 제일 마지막 배열인자 비교
        else{
            //A가 더 클 때
            if(A->a[A->word_len-1] > B->a[B->word_len-1]){
                return A_sign;
            }
            //B가 더 클 때
            else if(A->a[A->word_len-1] < B->a[B->word_len-1]){
                return (-1)*A_sign;
            }
            else{
                return 0;
            }
        }
    }
}

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
    msg error_msg = 0;
    word result;
    int max_len;
    int c = 0;
    
    max_len = src1->word_len;
    error_msg = bi_new(dst, max_len + 1);   //더 긴 길이의 bigint만큼 생성

    if(error_msg == FAILED)
    {
        return FAILED;
    }

    if(src1->sign == POSITIVE){
        (*dst)->sign = POSITIVE;
    }
    else{
        (*dst)->sign = NEGATIVE;
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

msg bi_add(bigint** dst, const bigint* src1, const bigint* src2){
    msg error_msg = FAILED;

    bigint* temp_src1 = NULL;
    bigint* temp_src2 = NULL;
    
    word temp1 = 0;
    word temp2 = 0;

    error_msg = bi_assign(&temp_src1, src1);
    if(error_msg == FAILED){
        return FAILED;
    }
    error_msg = bi_assign(&temp_src2, src2);
    if(error_msg == FAILED){
        return FAILED;
    }

    for(int index = 0; index < temp_src1->word_len; index++)
    {
        temp1 |= temp_src1->a[index];
    }
    for(int index = 0; index < temp_src2->word_len; index++)
    {
        temp2 |= temp_src2->a[index];
    }

    if(temp1 == 0){
        error_msg = bi_assign(dst, temp_src2);
    }
    else if(temp2 == 0){
        error_msg = bi_assign(dst, temp_src1);
    }
    else if((temp_src1->sign == POSITIVE) && (temp_src2->sign == NEGATIVE)){
        temp_src2->sign = POSITIVE;
        error_msg = bi_sub(dst, temp_src1, temp_src2);
    }
    else if((temp_src1->sign ==  NEGATIVE) && (temp_src2->sign ==  POSITIVE)){
        temp_src1->sign = POSITIVE;
        error_msg = bi_sub(dst, temp_src2, temp_src1);
    }
    else if ((bi_compare(temp_src1, temp_src2) == 1) || (bi_compare(temp_src1, temp_src2) == 0)){
        error_msg = add_same_sign(dst, temp_src1, temp_src2);
    }
    else{   
        error_msg = add_same_sign(dst, temp_src2, temp_src1);
    }

    error_msg = bi_delete(&temp_src1);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    error_msg = bi_delete(&temp_src2);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    return SUCCESS;
}

word sub_adb(word A, char* borrow, word B)
{
    char borrow_buf = 0;
    word C = A - (*borrow);

    if(A < (word)*borrow)
    {
        borrow_buf = 1;
    }

    if(C < B)
    {
        borrow_buf += 1;
    }

    C = C - B;

    *borrow = borrow_buf;
    return C;
}

msg bi_subc(bigint** dst, bigint* src1, bigint* src2)
{
    msg error_msg = 0;
    error_msg = bi_fillzero(&src2, src1->word_len);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    
    error_msg = bi_new(dst, src1->word_len);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    (*dst)->sign = POSITIVE;
    
    char borrow = 0;

    for (int index = 0; index<(src2->word_len); index++)
    {
        (*dst)->a[index] = sub_adb(src1->a[index], &borrow, src2->a[index]);
    }
    
    return bi_refine(*dst);
}

msg bi_sub(bigint** dst, const bigint* src1, const bigint* src2)
{
    msg error_msg = FAILED;

    bigint* temp_src1 = NULL;
    bigint* temp_src2 = NULL;
    word temp1 = 0;
    word temp2 = 0;

    error_msg = bi_assign(&temp_src1, src1);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    error_msg = bi_assign(&temp_src2, src2);
    if(error_msg == FAILED)
    {
        return FAILED;
    }

    for(int index = 0; index < temp_src1->word_len; index++)
    {
        temp1 |= temp_src1->a[index];
    }
    for(int index = 0; index < temp_src2->word_len; index++)
    {
        temp2 |= temp_src2->a[index];
    }
    if(temp1 == 0)
    {
        temp_src2->sign = (temp_src2->sign == POSITIVE) ? NEGATIVE : POSITIVE;
        error_msg = bi_assign(dst, temp_src2);
    }
    else if(temp2 == 0)
    {
        error_msg = bi_assign(dst, temp_src1);
    }
    else if(bi_compare(temp_src1, temp_src2) == 0)
    {
        error_msg = bi_new(dst, 1);
    }
    else if((bi_compare(temp_src1, temp_src2) == 1) && (temp_src2->sign == POSITIVE))
    {
        error_msg = bi_subc(dst, temp_src1, temp_src2);
    }
    else if((bi_compare(temp_src1, temp_src2) == -1) && (temp_src1->sign == POSITIVE))
    {
        error_msg = bi_subc(dst, temp_src2, temp_src1);
        (*dst)->sign = NEGATIVE;
    }
    else if((bi_compare(temp_src1, temp_src2) == 1) && (temp_src1->sign == NEGATIVE))
    {
        temp_src1->sign = temp_src2->sign = POSITIVE;
        error_msg = bi_subc(dst, temp_src2, temp_src1);
    }
    else if((bi_compare(temp_src1, temp_src2) == -1) && (temp_src2->sign == NEGATIVE))
    {
        temp_src1->sign = temp_src2->sign = POSITIVE;
        error_msg = bi_subc(dst, temp_src1, temp_src2);
        (*dst)->sign = NEGATIVE;
    }
    else if((temp_src1->sign == POSITIVE) && (temp_src2->sign == NEGATIVE))
    {
        temp_src2->sign = POSITIVE;
        printf("ADD 실행1\n");
        error_msg = bi_add(dst, temp_src1, temp_src2);
    }
    else
    {
        temp_src1->sign = POSITIVE;
        printf("ADD 실행2\n");
        error_msg = bi_add(dst, temp_src1, temp_src2);
        (*dst)->sign = ((*dst)->sign == POSITIVE) ? NEGATIVE : POSITIVE;
    }

    if(error_msg == FAILED)
    {
        return FAILED;
    }
    error_msg = bi_delete(&temp_src1);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    error_msg = bi_delete(&temp_src2);
    if(error_msg == FAILED)
    {
        return FAILED;
    }

    return SUCCESS;
}

