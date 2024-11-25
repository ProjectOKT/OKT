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
        if(A->sign == ZERO)
        {
            return (-1) * B->sign;
        }
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
        // 길이가 같을 때 제일 마지막 배열인자 까지 비교
        else{
            for (int i = 1; i <= A->word_len; i++){
                //A가 더 클 때
                if(A->a[A->word_len-i] > B->a[B->word_len-i]){
                    return A_sign;
                }
                //B가 더 클 때
                else if(A->a[A->word_len-i] < B->a[B->word_len-i]){
                    return (-1)*A_sign;
                }
            }
            //모두 같을 때
            return 0;
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
    if(result < (word)*c){
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
    
    if((*dst) != NULL)
    {
        error_msg = bi_delete(dst);
        if(error_msg == FAILED )
        {
            return FAILED;
        }
    }

    if(src1->sign == POSITIVE){   //더 긴 길이의 bigint만큼 생성
        max_len = src1->word_len;
        error_msg = bi_new(dst, max_len + 1);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
        (*dst)->sign = POSITIVE;
    }
    else{
        max_len = src2->word_len;
        error_msg = bi_new(dst, max_len + 1);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
        (*dst)->sign = NEGATIVE;          //더 긴 길이의 bigint만큼 생성
    }

    if((src1->word_len) > (src2->word_len)){
        error_msg = bi_fillzero(src2, src1->word_len, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }
    else{
        error_msg = bi_fillzero(src1, src2->word_len, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }

    for(int idx = 0; idx < max_len; idx++){    
        result = add_c(src1->a[idx], src2->a[idx], &c);
        (*dst)->a[idx] = result;
    }
    if(c == 1){
        (*dst)->a[max_len] = 1;        //마지막 carry가 1이면 src1 크기를 넘어간다.
    }
    else{
        error_msg = bi_refine(*dst);             //마지막 carry가 0이면 크기 조절 후 마무리
    }
    if(error_msg == FAILED)
    {
        return FAILED;
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
    error_msg = bi_fillzero(src2, src1->word_len, TOP);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    
    if((*dst) != NULL)
    {
        error_msg = bi_delete(dst);
        if(error_msg == FAILED )
        {
            return FAILED;
        }
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
        if(temp_src2->sign != ZERO)
        {
            temp_src2->sign = (temp_src2->sign == POSITIVE) ? NEGATIVE : POSITIVE;
        }
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
        error_msg = bi_add(dst, temp_src1, temp_src2);
    }
    else
    {
        temp_src1->sign = POSITIVE;
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

/**
 * @brief Multiplication two single words
 * 
 * This function performs multiplication between two words (`src1` and `src2`) and 
 * stores the result in a bigint structure pointed to by `dst`. It handles the multiplication
 * by dividing each word into half-word, then products and adds each others.
 * 
 * @param[out] dst Pointer to the result bigint that will store the result of the multiplication.
 *                 The function allocates memory for this bigint and initializes its elements.
 * @param[in] src1 The first operand for the multiplication.
 * @param[in] src2 The second operand for the multiplication.
 * 
 * @return Returns 1 on success, -1 on failure.
 * 
 */
msg bi_smul(OUT bigint** dst, IN word src1, IN word src2)
{
    int error_msg = 0;

    error_msg = bi_new(dst, 2);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    (*dst)->sign = POSITIVE;

    half_word A1 = 0, A0 = 0, B1 = 0, B0 = 0;
    word temp, temp1 = 0, temp0 = 0;

    A1 = src1 >> (sizeof(half_word) * 8);
    A0 = src1 & (((word)1 << (sizeof(half_word) * 8)) - 1);

    B1 = src2 >> (sizeof(half_word) * 8);
    B0 = src2 & (((word)1 << (sizeof(half_word) * 8)) - 1);

    temp1 = (word)A1 * (word)B0;
    temp0 = (word)A0 * (word)B1;
    temp0 += temp1;
    temp1 = (temp0 < temp1);

    (*dst)->a[1] = (word)A1 * (word)B1;
    temp = (*dst)->a[0] = (word)A0 * (word)B0;
    
    (*dst)->a[0] += temp0 << (sizeof(half_word) * 8);
    (*dst)->a[1] += (temp1 << (sizeof(half_word) * 8)) + (temp0 >> (sizeof(half_word) * 8)) + ((*dst)->a[0] < temp);
    
    return SUCCESS;
}

/**
 * @brief Multiplication two multi-word size integers with the non-negative integer
 * 
 * This function performs the Multiplication of two big non-negative integers (`src1` and `src2`), 
 * This Improved Multiplication performs single words mul by smul and connects result of smul.
 * The result is addtion of the results connected sigle words mul with shifting and zero padding.
 * 
 * @param[out] dst Pointer to the result bigint that will hold the result of the non-negative multiplication.
 * @param[in] src1 The first operand for the multiplication.
 * @param[in] src2 The second operand for the multiplication.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_mulc(OUT bigint** dst, IN bigint* src1, IN bigint* src2)
{   
    int error_msg = 0;
    bigint* temp0 = NULL;
    bigint* temp1 = NULL;
    bigint* temp = NULL;
    bigint* tempC = NULL;
    bigint* tempC_result = NULL;
    bigint* tempT0 = NULL;
    bigint* tempT1 = NULL;
    bigint* tempT0_result = NULL;
    bigint* tempT1_result = NULL;

    if(error_msg == FAILED)
    {
        return FAILED;
    }

    if((*dst) != NULL)
    {
        error_msg = bi_delete(dst);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }

    error_msg = bi_new(&tempC, 1);
    tempC->sign = POSITIVE;

    if((src1->word_len) % 2 == 1)
    {
        error_msg = bi_fillzero(src1, src1->word_len + 1, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }   
    }
    if((src2->word_len) % 2 == 1)
    {
        error_msg = bi_fillzero(src2, src2->word_len + 1, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }
    for(int idx2 = 0; idx2 < src2->word_len; idx2++){
        bi_new(&tempT1, 1);
        tempT0 = NULL;
        for(int idx1 = 0; idx1 < (src1->word_len)/ 2; idx1++){
            bi_smul(&temp0, src1->a[2*idx1], src2->a[idx2]);
            bi_smul(&temp1, src1->a[2*idx1 + 1], src2->a[idx2]);
            bi_connect(&tempT0_result, temp0, tempT0);
            bi_connect(&tempT1_result, temp1, tempT1);
            bi_assign(&tempT0, tempT0_result);
            bi_assign(&tempT1, tempT1_result);

            bi_delete(&tempT0_result);
            bi_delete(&tempT1_result);
            bi_delete(&temp0);
            bi_delete(&temp1);
        }
        if (bi_compare(tempT1, tempT0) == 1){
            add_same_sign(&temp, tempT1, tempT0);

            bi_delete(&tempT1);
            bi_delete(&tempT0);
        }
        else{
            add_same_sign(&temp, tempT0, tempT1);

            bi_delete(&tempT1);
            bi_delete(&tempT0);
        }
        bi_fillzero(temp, temp->word_len + idx2, BOTTOM);
        if (bi_compare(temp, tempC) == 1){
            add_same_sign(&tempC_result, temp, tempC);
        }
        else
        {
            add_same_sign(&tempC_result, tempC, temp);
        }
        bi_assign(&tempC, tempC_result);
    }


    bi_assign(dst, tempC);
    bi_delete(&tempC);
    bi_delete(&temp);
    bi_delete(&tempC_result);
    bi_delete(&tempT0);
    bi_delete(&tempT1);
    return SUCCESS;
}

/**
 * @brief Multiplication two big integers
 * 
 * This function performs the Multiplication of two big integers (`src1` and `src2`), 
 * This Multiplication performs multiplication by Improved Multiplication.
 * Consider sign of two integers, as the result of the muliplication with two negative integers is negative.
 * 
 * @param[out] dst Pointer to the result bigint that will hold the result of the multiplication.
 * @param[in] src1 The first big integer for the multiplication.
 * @param[in] src2 The second big integer for the multiplication.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_mul(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2)
{
    msg error_msg = FAILED;

    bigint* temp_src1 = NULL;
    bigint* temp_src2 = NULL;

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

    if((temp_src1->sign == ZERO) || (temp_src2->sign == ZERO))
    {
        error_msg = bi_new(dst, 1);
        if(((*dst)->word_len != 1) || ((*dst)->a[0] != 0)){
            fprintf(stderr, ERR_MEMORY_ALLOCATION);
        }
    }
    else if((temp_src1->word_len == 1) && (temp_src1->a[0] == 1))
    {
        error_msg = bi_assign(dst, temp_src2);
        (*dst)->sign = ((temp_src1->sign) == (temp_src2->sign)) ? POSITIVE : NEGATIVE;
    }
    else if((temp_src2->word_len == 1) && (temp_src2->a[0] == 1))
    {
        error_msg = bi_assign(dst, temp_src1);
        (*dst)->sign = ((temp_src1->sign) == (temp_src2->sign)) ? POSITIVE : NEGATIVE;
    }
    else
    {
        error_msg = bi_mulc(dst, temp_src1, temp_src2);
        (*dst)->sign = ((temp_src1->sign) == (temp_src2->sign)) ? POSITIVE : NEGATIVE;
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


/**
 * @brief Multiplication two big integers
 * 
 * This function performs the Karatsuba Multiplication of two big integers (`src1` and `src2`), 
 * This Multiplication performs multiplication by Karatsuba Multiplication.
 * Consider sign of two integers, as the result of the muliplication with two negative integers is positive.
 * 
 * @param[out] dst Pointer to the result bigint that will hold the result of the multiplication.
 * @param[in] src1 The first big integer for the multiplication.
 * @param[in] src2 The second big integer for the multiplication.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
#define min(a,b)  ((a) <= (b) ? (a) : (b))
#define max(a,b)  ((a) >= (b) ? (a) : (b))

int get_sign(bigint* src){
    if (src->sign == NEGATIVE) return 1;
    return 0;
} 

msg bi_mul_k(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2)
{
    bigint* temp_src1 = NULL;
    bigint* temp_src2 = NULL;
    
    bi_assign(&temp_src1, src1);
    bi_assign(&temp_src2, src2);
    temp_src1->sign = POSITIVE;
    temp_src2->sign = POSITIVE;

    int n = src1->word_len;
    int m = src2->word_len;

    //flag
    if (10 >= min(n,m)) {
        bi_mul(dst,temp_src1,temp_src2);
        bi_delete(&temp_src1);
        bi_delete(&temp_src2);
        return SUCCESS;
    }

    bigint* a1 = NULL;
    bigint* a0 = NULL; 
    bigint* b1 = NULL;
    bigint* b0 = NULL; 
    bigint* t1 = NULL;
    bigint* t0 = NULL;
    bigint* r = NULL;
    bigint* s1 = NULL;
    bigint* s0 = NULL;
    bigint* s = NULL;
    bigint* temp = NULL;
    bigint* sum_s = NULL;

    //5
    int l = (max(n,m) + 1) >> 1;
    int lw = l*SIZEOFWORD;
    // a >> lw
    bi_assign(&a1, temp_src1);
    bi_bit_rshift(a1,lw);
    //a mod 
    bi_assign(&a0, temp_src1);
    if (a0->word_len > l){
        for (int i = l; i < a0->word_len; i++)
        {
            a0->a[i] = 0;
        }
    }
    
    bi_delete(&temp_src1);
    
    // b >> lw
    bi_assign(&b1, temp_src2);
    bi_bit_rshift(b1,lw);
    //b mod 
    bi_assign(&b0, temp_src2);
    if (b0->word_len > l){
        for (int i = l; i < b0->word_len; i++)
        {
            b0->a[i] = 0;
        }
    }
    bi_delete(&temp_src2);
    bi_refine(a0);
    bi_refine(b0);
    bi_refine(a1);
    bi_refine(b1);
    // t1, t0
    bi_mul_kara(&t1, a1, b1);
    bi_mul_kara(&t0, a0, b0);
    
    // r = (t1 << 2*lw) + t0
    bi_assign(&temp, t1);
    bi_bit_lshift(temp,2*lw);
    bi_add(&r, temp, t0);
    
    // s1 = a0 - a1
    bi_sub(&s1,a0,a1);
    bi_delete(&a1);
    bi_delete(&a0);
    // s0 = b1 - b0
    bi_sub(&s0,b1,b0);
    bi_delete(&b1);
    bi_delete(&b0);
    //24,25
    int s_sign = 0;
    if (get_sign(s1) == get_sign(s0)){
        s_sign = POSITIVE;
    }
    else {
        s_sign = NEGATIVE;
    }
    s1->sign = POSITIVE;
    s0->sign = POSITIVE;
    bi_mul_kara(&s,s1,s0);
    bi_delete(&s0);
    bi_delete(&s1);
    s->sign = s_sign;
    //s = s + t1
    bi_add(&temp,s,t1);

    bi_delete(&t1);
    bi_delete(&s);
    //s = s + t0
    bi_add(&sum_s,temp,t0);

    bi_delete(&temp);
    bi_delete(&t0);
    //s = s << lw
    bi_bit_lshift(sum_s,lw);
    bi_add(dst,r,sum_s);
    bi_delete(&sum_s);
    bi_delete(&r);

    return SUCCESS;
}


msg bi_mul_kara(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2)
{
    bi_mul_k(dst,src1,src2);
    if (src1->sign == ZERO || src2->sign == ZERO){
        (*dst)->sign= ZERO;
    }
    else if(src1->sign != src2->sign){
        (*dst)->sign= NEGATIVE;
    }
    else{
        (*dst)->sign= POSITIVE;
    }

    return SUCCESS;
}


/**
 * @brief Binary long division of two big integers.
 * 
 * This function performs binary long division of two big integers (`src1` and `src2`), computing both the quotient and remainder.
 * The division is performed bit-by-bit, starting from the most significant bit of the dividend. 
 * The function assumes that the divisor (`src2`) is positive and that the dividend (`src1`) is greater than or equal to the divisor.
 * 
 * The `quotient` is always positive, and the `remainder` is adjusted to its correct value. If the remainder is zero, 
 * its sign is explicitly set to `ZERO`.
 * 
 * If any error occurs (e.g., invalid input or memory allocation failure), the function returns an error.
 * 
 * @param[out] quotient Pointer to the result bigint that will hold the quotient of the division.
 * @param[out] remainder Pointer to the result bigint that will hold the remainder of the division.
 * @param[in] src1 The dividend big integer for the division.
 * @param[in] src2 The divisor big integer for the division.
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid input or memory allocation error).
 */
msg bi_binary_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2)
{
    int error_msg = FAILED;
    int word_bit_size = 0;
    int divc_num = 0;

    if (src1 == NULL || src2 == NULL || !((src2->sign == POSITIVE) && (bi_compare(src1, src2) >= 0)))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    word_bit_size = sizeof(word) * 8;
    divc_num = (src1->word_len * word_bit_size) - 1;

    error_msg = bi_new(quotient, src1->word_len - src2->word_len + 1);
    if (error_msg == FAILED)
    {
        return FAILED;
    }
    (*quotient)->sign = POSITIVE;

    error_msg = bi_new(remainder, 1);
    if (error_msg == FAILED)
    {
        return FAILED;
    }
    (*remainder)->sign = POSITIVE;

    for(int bitindex = divc_num; bitindex >= 0; bitindex--)
    {
        error_msg = bi_bit_lshift(*remainder, 1);
        if (error_msg == FAILED)
        {
            return FAILED;
        }
        (*remainder)->a[0] ^= (src1->a[bitindex / word_bit_size] >> (bitindex % word_bit_size) & (0x01));

        if (bi_compare(*remainder, src2) >= 0)
        {
            (*quotient)->a[bitindex / word_bit_size] ^= (word)1<<(bitindex % word_bit_size);
            error_msg = bi_sub(remainder, *remainder, src2);
            if(error_msg == FAILED)
            {
                return FAILED;
            }
        }
    }

    error_msg = bi_refine(*quotient);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    
    if((*remainder)->word_len == 1 && (*remainder)->a[0] == 0)
    {
        (*remainder)->sign = ZERO;
    }

    return SUCCESS;
}


/**
 * @brief Division of two big integers.
 * 
 * This function performs the division of two big integers (`src1` and `src2`), computing both the quotient and remainder. 
 * The function handles positive and negative values for the input integers. The signs of the `quotient` and `remainder` 
 * are determined based on the signs of the input integers:
 * 
 * - Division between two integers with the same sign produces a positive `quotient`.
 * - Division between two integers with different signs produces a negative `quotient`.
 * - The `remainder` always takes the same sign as the divisor (`src2`).
 * 
 * If the division is not possible (e.g., `src2` is zero), the function returns an error.
 * 
 * @param[out] quotient Pointer to the result bigint that will hold the quotient of the division.
 * @param[out] remainder Pointer to the result bigint that will hold the remainder of the division.
 * @param[in] src1 The dividend big integer for the division.
 * @param[in] src2 The divisor big integer for the division.
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid input or division by zero).
 */
msg bi_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2)
{
    int error_msg = SUCCESS;

    bigint* temp_src1 = NULL;
    bigint* temp_src2 = NULL;
    
    if((src1 == NULL) || (src2 == NULL))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    error_msg = bi_assign(&temp_src1, src1);
    if (error_msg == FAILED) return FAILED;
    error_msg = bi_assign(&temp_src2, src2);
    if (error_msg == FAILED)
    {   
        bi_delete(&temp_src1);
        return FAILED;
    }

    if (((src1->sign == POSITIVE) && (src2->sign == POSITIVE)) || ((src1->sign == NEGATIVE) && (src2->sign == NEGATIVE)))
    {
        temp_src1->sign = POSITIVE;
        temp_src2->sign = POSITIVE;
        if (bi_compare(temp_src1, temp_src2) >= 0)
        {
            error_msg = bi_binary_long_division(quotient, remainder, temp_src1, temp_src2);
        }
        else
        {
            error_msg = (bi_new(quotient, 1) == FAILED || bi_assign(remainder, temp_src1) == FAILED) ? FAILED : SUCCESS;
        }
        (*remainder)->sign = src2->sign;
    }
    else if (((src1->sign == POSITIVE) && (src2->sign == NEGATIVE)) || ((src1->sign == NEGATIVE) && (src2->sign == POSITIVE)))
    {
        temp_src1->sign = temp_src2->sign = POSITIVE;
        if (bi_compare(temp_src1, temp_src2) >= 0)
        {
            error_msg = bi_binary_long_division(quotient, remainder, temp_src1, temp_src2);
            if((*remainder)->sign == ZERO)
            {
                (*quotient)->sign = NEGATIVE;
            }
            else
            {
                bi_sub(remainder, temp_src2, *remainder);
                (*remainder)->sign = src2->sign;
                bi_new(&temp_src1, 1);
                temp_src1->sign = POSITIVE;
                temp_src1->a[0] = 1;
                bi_add(quotient, *quotient, temp_src1);
                (*quotient)->sign = NEGATIVE;
            }
        }
        else
        {
            bi_new(quotient, 1);
            (*quotient)->a[0] = 1;
            (*quotient)->sign = NEGATIVE;
            bi_add(remainder, src1, src2);
        }
    }
    else if ((src1->sign == ZERO) && (src2->sign != ZERO))
    {
        error_msg = bi_new(quotient, 1) == FAILED || bi_new(remainder, 1) == FAILED ? FAILED : SUCCESS;
    }
    else
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        
        error_msg = FAILED;
    }
    
    error_msg = error_msg == FAILED || bi_delete(&temp_src1) == FAILED || bi_delete(&temp_src2) == FAILED ? FAILED : SUCCESS;
    
    return error_msg;
}

/**
 * @brief Squaring of single word.
 * 
 * This function performs Squaring of single word (`src1`)
 * The sign of the result is always POSITIVE.
 * 
 * @param[out] dst Pointer to the result bigint that squared by src1.
 * @param[in] src1 The single word for the squaring.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_squc(OUT bigint** dst, IN const word src1)
{   
    int error_msg = 0;
    half_word A1 = 0, A0 = 0;
    bigint* C = NULL;
    bigint* T = NULL;

    if((*dst) != NULL)
    {
        error_msg = bi_delete(dst);
 
    }
    
    error_msg = bi_new(dst, 2);


    error_msg = bi_new(&C, 2);

    C->sign = POSITIVE;

    error_msg = bi_new(&T, 1);

    T->sign = POSITIVE;

    A1 = src1 >> (sizeof(half_word) * 8);
    A0 = src1 & (((word)1 << (sizeof(half_word) * 8)) - 1);
    C->a[1] = A1*A1;
    C->a[0] = A0*A0;
    T->a[0] = A0*A1;
    error_msg = bi_bit_lshift(T, SIZEOFWORD/2 + 1);


    error_msg = add_same_sign(dst, C, T);

    bi_delete(&C);
    bi_delete(&T);

    if(error_msg == FAILED )
    {
        return FAILED;
    }

    return SUCCESS;
}

/**
 * @brief Squaring of positive or negative bigint.
 * 
 * This function performs Squaring of big int (`src1`)
 * The sign of the result is always POSITIVE.
 * It's like to multiplication of two same bigint.
 * By multiply 2 after the multiplication same single word, and connect the result of single word squaring.
 * 
 * @param[out] dst Pointer to the result bigint that squared by src1.
 * @param[in] src1 The single word for the squaring.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_squ(OUT bigint** dst, IN const bigint* src1)
{
    bigint* C1 = NULL;
    bigint* C2 = NULL;
    bigint* C1_sum = NULL;
    bigint* C2_sum = NULL;
    bigint* T1 = NULL;
    bigint* T2 = NULL;
    bigint* temp_src1 = NULL;

    if(src1->sign == ZERO)
    {
        bi_new(dst, 1);

        if(dst == NULL){
            return FAILED;
        }
        return SUCCESS;
    }
    
    bi_assign(&temp_src1, src1);

    bi_new(&C2, 1);
    
    for(int idx1 = 0; idx1 < temp_src1->word_len; idx1++)
    {
        bi_squc(&T1, temp_src1->a[idx1]);

        if(T1->word_len == 1)
        {
            bi_fillzero(T1, 2, TOP);
        }
        bi_connect(&C1_sum, T1, C1);

        bi_assign(&C1, C1_sum);

        for(int idx2 = idx1 + 1; idx2 < temp_src1->word_len; idx2++)
        {
            bi_smul(&T2, temp_src1->a[idx1], temp_src1->a[idx2]);

            bi_bit_lshift(T2, (idx1 + idx2) * SIZEOFWORD);

            bi_add(&C2_sum, C2, T2);

            bi_assign(&C2, C2_sum);

            bi_delete(&C2_sum);
            bi_delete(&T2);
        }
        bi_delete(&T1);
        bi_delete(&C1_sum);
    }

    bi_bit_lshift(C2, 1);

    bi_add(dst, C1, C2);
    bi_refine(*dst); // sungbin: NOV_24 추가
    
    bi_delete(&temp_src1);
    bi_delete(&C1);
    bi_delete(&C2);
    return SUCCESS;
}


/**
 * @brief karatsuba squaring of big integer.
 * 
 * This function performs the karatsuba squaring of two big integer (`src`). 
 * The function handles positive and for the input integer. 
 *  
 * @param[in] src The squaring big integer.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_squ_kara(OUT bigint** dst, IN const bigint* src)
{
    if (src->sign == ZERO){
        (*dst)->sign = ZERO;
        return SUCCESS;
    }
    int n = src->word_len;

    //flag
    if (10 >= n) {
        bi_squ(dst,src);
        return SUCCESS;
    }

    bigint* a1 = NULL;
    bigint* a0 = NULL; 
    bigint* t1 = NULL;
    bigint* t0 = NULL;
    bigint* r = NULL;
    bigint* s = NULL;
    bigint* temp_src = NULL;
    
    bi_assign(&temp_src, src);
    temp_src->sign = POSITIVE;
    //5
    int l = (n + 1) >> 1;
    int lw = l*SIZEOFWORD;
    // a >> lw
    bi_assign(&a1, temp_src);
    bi_bit_rshift(a1,lw);
    //a mod 
    bi_assign(&a0, temp_src);
    bi_delete(&temp_src);
    for (int i = l; i < n; i++)
    {
        a0->a[i] = 0;
    }
    bi_refine(a0);
    bi_refine(a1);
    // t1, t0
    bi_squ_kara(&t1, a1);
    bi_squ_kara(&t0, a0);
    // r = (t1 << 2*lw) + t0
    bi_bit_lshift(t1,2*lw);
    bi_add(&r, t1, t0);
    bi_delete(&t1);
    bi_delete(&t0);
    
    bi_mul_kara(&s,a1,a0);
    bi_delete(&a1);
    bi_delete(&a0);

    bi_bit_lshift(s, (lw+1));
    bi_add(dst,r,s);
    (*dst)->sign = POSITIVE;
    bi_delete(&s);
    bi_delete(&r);

    return SUCCESS;
}


/**
 * @brief Modular exponentiation using left-to-right binary method.
 * 
 * This function computes the modular exponentiation (`base^exp % mod`) 
 * using the left-to-right binary method. The result is stored in `dst`. 
 * 
 * @param[out] dst Pointer to the output big integer result.
 * @param[in] base The base big integer.
 * @param[in] exp The exponent big integer.
 * @param[in] mod The modulus big integer.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_mod_exp_l2r(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod)
{
    if((base == NULL)|| (exp == NULL) || (mod == NULL) || (base->a == NULL) || 
        (exp->a == NULL) || (mod->a == NULL) || (base->sign != POSITIVE) || (exp->sign != POSITIVE) || (mod->sign != POSITIVE))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    bigint* quotient_buf = NULL;

    bi_new(dst, 1);
    (*dst)->sign = POSITIVE;
    (*dst)->a[0] = 1;

    for(int word_index = exp->word_len - 1; word_index >= 0; word_index--)
    {
        for(int bit_index = sizeof(word) * 8 - 1; bit_index >= 0; bit_index--)
        {
            bi_squ(dst, *dst);
            bi_division(&quotient_buf, dst, *dst, mod);
            if((exp->a[word_index] >> bit_index) & 0x01)
            {
                bi_mul(dst, *dst, base);
                bi_division(&quotient_buf, dst, *dst, mod);
            }
        }
    }

    bi_delete(&quotient_buf);

    return SUCCESS;
}


/**
 * @brief Modular exponentiation using right-to-left binary method.
 * 
 * This function computes the modular exponentiation (`base^exp % mod`) 
 * using the right-to-left binary method. The result is stored in `dst`.
 * 
 * @param[out] dst Pointer to the output big integer result.
 * @param[in] base The base big integer.
 * @param[in] exp The exponent big integer.
 * @param[in] mod The modulus big integer.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_mod_exp_r2l(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod)
{
    if((base == NULL)|| (exp == NULL) || (mod == NULL) || (base->a == NULL) || 
        (exp->a == NULL) || (mod->a == NULL) || (base->sign != POSITIVE) || (exp->sign != POSITIVE) || (mod->sign != POSITIVE))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    bigint* quotient_buf = NULL;
    bigint* t1 = NULL;

    bi_new(dst, 1);
    (*dst)->sign = POSITIVE;
    (*dst)->a[0] = 1;

    bi_assign(&t1, base);

    for(int word_index = 0; word_index < exp->word_len; word_index++)
    {
        for(int bit_index = 0; bit_index < (int)(sizeof(word) * 8); bit_index++)
        {
            if((exp->a[word_index] >> bit_index) & 0x01)
            {
                bi_mul(dst, *dst, t1);
                bi_division(&quotient_buf, dst, *dst, mod);
            }
            bi_squ(&t1, t1);
            bi_division(&quotient_buf, &t1, t1, mod);
        }
    }

    bi_delete(&quotient_buf);
    bi_delete(&t1);

    return SUCCESS;
}
