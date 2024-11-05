#include <stdio.h>


#include "operation.h"
#include "bigintfun.h"
#include "params.h"
#include "errormsg.h"


/**
 * @brief Compares two bigint values.
 * 
 * This function compares two `bigint` structures, returning a value that indicates
 * their relative sizes. It takes into account the sign of the bigints and their
 * lengths to determine the result.
 * 
 * @param[in] A Pointer to the first `bigint` structure to be compared.
 * @param[in] B Pointer to the second `bigint` structure to be compared.
 * 
 * @return 
 *   - 1 if `A` is greater than `B`,
 *   - 0 if `A` is equal to `B`,
 *   - -1 if `A` is less than `B`.
 */
int bi_compare(IN const bigint* A, IN const bigint* B){
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


/**
 * @brief Adds two words with a carry value.
 * 
 * This function computes the sum of two `word` values (`src1` and `src2`) along 
 * with a carry value. It returns the result of the addition and updates the carry 
 * pointer to reflect any overflow.
 * 
 * @param[in] src1 The first `word` to be added.
 * @param[in] src2 The second `word` to be added.
 * @param[in,out] c Pointer to an integer representing the carry. This value 
 *                  is updated to reflect any overflow after the addition.
 * 
 * @return The result of the addition of `src1`, `src2`, and the carry.
 */
word add_c(IN word src1, IN word src2, IN int* c){
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


/**
 * @brief Adds two bigint values with the same sign.
 * 
 * This function adds two `bigint` structures (`src1` and `src2`) that are both
 * either positive or negative. The result is stored in a newly allocated `bigint`
 * structure pointed to by `dst`. The function ensures that the resulting bigint
 * has the appropriate length and sign.
 * 
 * @param[out] dst Pointer to a pointer of the resulting `bigint` after addition.
 * @param[in] src1 Pointer to the first `bigint` to be added.
 * @param[in] src2 Pointer to the second `bigint` to be added. 
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg add_same_sign(OUT bigint** dst, IN bigint* src1, IN bigint* src2){
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
        bi_fillzero(src2, src1->word_len);
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


/**
 * @brief Adds two bigint values.
 * 
 * This function performs the addition of two `bigint` structures (`src1` and `src2`),
 * taking into account their signs. It handles cases where either or both of the 
 * `bigint` values are zero, as well as cases where the values have different signs. 
 * The result is stored in a newly allocated `bigint` structure pointed to by `dst`.
 * 
 * @param[out] dst Pointer to a pointer of the resulting `bigint` after addition.
 * @param[in] src1 Pointer to the first `bigint` to be added.
 * @param[in] src2 Pointer to the second `bigint` to be added. 
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_add(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2){
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


/**
 * @brief Subtracts two words with borrow handling.
 * 
 * This function performs the subtraction of two words, `A` and `B`, taking into 
 * account a borrow value. It updates the borrow status and returns the result of 
 * the subtraction.
 * 
 * @param[in] A The first word from which the borrow-adjusted `B` will be subtracted.
 * @param[in,out] borrow A pointer to the current borrow value, which will be updated.
 * @param[in] B The second word to be subtracted from `A` after adjusting for borrow.
 * 
 * @return The result of the subtraction of `B` from `A`, adjusted for borrow.
 */
word sub_adb(IN word A, IN char* borrow, IN word B)
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


/**
 * @brief Subtracts one bigint from another with borrow handling.
 * 
 * This function performs the subtraction of two big integers (`src1` and `src2`), 
 * taking into account any borrows that occur during the subtraction process. 
 * The result is stored in a newly allocated bigint pointed to by `dst`.
 * 
 * @param[out] dst Pointer to the result bigint that will hold the result of the subtraction.
 * @param[in] src1 The minuend (the bigint from which `src2` will be subtracted).
 * @param[in] src2 The subtrahend (the bigint to be subtracted from `src1`).
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_subc(OUT bigint** dst, IN bigint* src1, IN bigint* src2)
{
    msg error_msg = 0;
    error_msg = bi_fillzero(src2, src1->word_len);
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


/**
 * @brief Subtracts one bigint from another.
 * 
 * This function performs the subtraction of two big integers (`src1` and `src2`),
 * considering their signs and magnitude. The result is stored in a newly allocated bigint
 * pointed to by `dst`. If `src1` is less than `src2`, the result will have a negative sign.
 * 
 * @param[out] dst Pointer to the result bigint that will hold the result of the subtraction.
 * @param[in] src1 The minuend (the bigint from which `src2` will be subtracted).
 * @param[in] src2 The subtrahend (the bigint to be subtracted from `src1`).
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_sub(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2)
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

