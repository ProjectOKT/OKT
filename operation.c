#include <stdio.h>
#include <stdlib.h>

#include "operation.h"
#include "bigintfun.h"
#include "params.h"
#include "errormsg.h"

/***********************************************
 * Addition
 ***********************************************/
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
msg bi_add(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2)
{
    msg error_msg = FAILED;

    bigint* temp_src1 = NULL;       
    bigint* temp_src2 = NULL;
    
    word temp1 = 0;
    word temp2 = 0;

    //src1, src2 -> temp_src1, temp_src2
    error_msg = bi_assign(&temp_src1, src1);
    if(error_msg == FAILED){
        return FAILED;
    }
    error_msg = bi_assign(&temp_src2, src2);
    if(error_msg == FAILED){
        return FAILED;
    }

    //check ZERO satisfy constant time
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
 * @brief Adds two bigint values and stores operator.
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
msg bi_add_replace(INOUT bigint** dst, IN const bigint* src1)
{
    msg error_msg = FAILED;

    bigint* temp_src1 = NULL;
    bigint* temp_dst = NULL;           

    word sum_dst = 0;
    word sum_temp1 = 0;

    error_msg = bi_assign(&temp_src1, src1);
    if(error_msg == FAILED){
        return FAILED;
    }
    error_msg = bi_assign(&temp_dst, *dst);
    if(error_msg == FAILED){
        return FAILED;
    }

    for(int index = 0; index < temp_src1->word_len; index++)
    {
        sum_temp1 |= temp_src1->a[index];
    }
    for(int index = 0; index < temp_dst->word_len; index++)
    {
        sum_dst |= temp_dst->a[index];
    }

    if(sum_temp1 == 0){
        error_msg = SUCCESS;
    }
    else if(sum_dst == 0){
        error_msg = bi_assign(dst, temp_src1);
    }
    else if((temp_src1->sign == POSITIVE) && (temp_dst->sign == NEGATIVE)){
        temp_dst->sign = POSITIVE;
        error_msg = bi_sub(dst, temp_src1, temp_dst);
    }
    else if((temp_src1->sign ==  NEGATIVE) && (temp_dst->sign ==  POSITIVE)){
        temp_src1->sign = POSITIVE;
        error_msg = bi_sub(dst, temp_dst, temp_src1);
    }
    else if ((bi_compare(temp_src1, temp_dst) == 1) || (bi_compare(temp_src1, temp_dst) == 0)){
        error_msg = add_same_sign_replace(&temp_dst, temp_src1);
        bi_assign(dst, temp_dst);
    }
    else{   
        error_msg = add_same_sign_replace(&temp_src1, temp_dst);
        bi_assign(dst, temp_src1);
    }

    error_msg = bi_delete(&temp_src1);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    error_msg = bi_delete(&temp_dst);
    if(error_msg == FAILED)
    {
        return FAILED;
    }

    return SUCCESS;
}

/***********************************************
 * Subtraction
 ***********************************************/
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

/***********************************************
 * Muliplication
 ***********************************************/
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
 * @brief Karatsuba Multiplication two big integers with signs
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

/***********************************************
 * Division
 ***********************************************/
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
msg bi_binary_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2)
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
        (*remainder)->sign = (((*remainder)->sign)!= ZERO) ? src2->sign : ZERO;
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

/***********************************************
 * Square
 ***********************************************/
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
    bi_new(&C1, 1);

    for(int idx1 = 0; idx1 < temp_src1->word_len; idx1++)
    {
        bi_squc(&T1, temp_src1->a[idx1]);
        bi_bit_lshift(T1, 2 * idx1 * SIZEOFWORD);
        bi_add_replace(&C1, T1);
        for(int idx2 = idx1 + 1; idx2 < temp_src1->word_len; idx2++)
        {
            bi_smul(&T2, temp_src1->a[idx1], temp_src1->a[idx2]);

            bi_bit_lshift(T2, (idx1 + idx2) * SIZEOFWORD);
            bi_add_replace(&C2, T2);
            bi_delete(&T2);
        }
        bi_delete(&T1);
    }

    bi_bit_lshift(C2, 1);
    bi_add(dst, C1, C2);
    
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

    if (KARA_FLAG_SQU >= n) {
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
    
    bi_mul_k(&s,a1,a0);
    bi_delete(&a1);
    bi_delete(&a0);

    bi_bit_lshift(s, (lw+1));
    bi_add(dst,r,s);
    (*dst)->sign = POSITIVE;
    bi_delete(&s);
    bi_delete(&r);

    return SUCCESS;
}

/***********************************************
 * Modular exponentiation
 ***********************************************/
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
            bi_squ_kara(dst, *dst);
            bi_word_division(&quotient_buf, dst, *dst, mod);
            if((exp->a[word_index] >> bit_index) & 0x01)
            {
                bi_mul_k(dst, *dst, base);
                bi_word_division(&quotient_buf, dst, *dst, mod);
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
                bi_mul_k(dst, *dst, t1);
                bi_word_division(&quotient_buf, dst, *dst, mod);
            }
            bi_squ_kara(&t1, t1);
            bi_word_division(&quotient_buf, &t1, t1, mod);
        }
    }

    bi_delete(&quotient_buf);
    bi_delete(&t1);

    return SUCCESS;
}


/**
 * @brief Modular exponentiation using multiply and square binary method.
 * 
 * This function computes the modular exponentiation (`base^exp % mod`) 
 * using the multiply and square binary method. The result is stored in `dst`.
 * 
 * @param[out] dst Pointer to the output big integer result.
 * @param[in] base The base big integer.
 * @param[in] exp The exponent big integer.
 * @param[in] mod The modulus big integer.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_mod_exp_MaS(OUT bigint** dst, IN const bigint* base, IN const bigint* exp, IN const bigint* mod)
{
    if((base == NULL)|| (exp == NULL) || (mod == NULL) || (base->a == NULL) || 
        (exp->a == NULL) || (mod->a == NULL) || (base->sign != POSITIVE) || (exp->sign != POSITIVE) || (mod->sign != POSITIVE))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    bigint* quotient_buf = NULL;
    bigint* t[2] = {NULL,NULL};

    bi_new(&t[0], 1);
    t[0]->sign = POSITIVE;
    t[0]->a[0] = 1;
    bi_new(&t[1], base->word_len);
    bi_assign(&t[1], base);

    for(int word_index = exp->word_len-1; word_index >= 0; word_index--)
    {
        for(int bit_index = (int)(sizeof(word) * 8) - 1; bit_index >= 0; bit_index--)
        {
            int n = (exp->a[word_index] >> bit_index) & 0x01;

            bi_mul_k(&t[1-n], t[0], t[1]);
            bi_squ_kara(&t[n],t[n]);
            bi_word_division(&quotient_buf, &t[0], t[0], mod);
            bi_word_division(&quotient_buf, &t[1], t[1], mod);
        }
    }
    bi_assign(dst,t[0]);
    bi_delete(&quotient_buf);
    bi_delete(&t[1]);
    bi_delete(&t[0]);

    return SUCCESS;
}

/***********************************************
 * Fast Reduction
 ***********************************************/
/**
 * @brief Fast Reduction using Barrett Reduction method.
 * 
 * This function computes the Fast Reduction (`base % mod`) 
 * using the Barrett Reduction method. The result is stored in `dst`.
 * 
 * @param[out] dst Pointer to the output big integer result.
 * @param[in] A The base big integer.
 * @param[in] T The pre-computed big integer.
 * @param[in] N The modulus big integer.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_bar_redu(OUT bigint** dst, IN const bigint* A, IN const bigint* T, IN const bigint* N)
{
    if((A == NULL)|| (T == NULL) || (N == NULL) || (A->a == NULL) || 
        (T->a == NULL) || (N->a == NULL) || (A->sign != POSITIVE) || (T->sign != POSITIVE) || (N->sign != POSITIVE))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    bigint* quotient_buf = NULL;
    bigint* R = NULL;
    bigint* temp = NULL;
    int n = N->word_len;

    bi_assign(&quotient_buf,A);

    bi_bit_rshift(quotient_buf,(n-1)*SIZEOFWORD);
    bi_mul_k(&quotient_buf,quotient_buf,T);

    bi_bit_rshift(quotient_buf,(n+1)*SIZEOFWORD);
    bi_mul_k(&R,N,quotient_buf);
    bi_delete(&quotient_buf);

    bi_assign(&temp,R);
    bi_sub(&R,A,temp);

    while((bi_compare(R,N) != -1)){
        bi_sub(&temp,R,N);
        bi_assign(&R,temp);
    }

    bi_assign(dst,R);

    bi_delete(&R);
    bi_delete(&temp);

    return SUCCESS;
}




/***********************************************
 * Division
 ***********************************************/
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
msg bi_word_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2)
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
            error_msg = bi_word_long_division(quotient, remainder, temp_src1, temp_src2);
        }
        else
        {
            error_msg = (bi_new(quotient, 1) == FAILED || bi_assign(remainder, temp_src1) == FAILED) ? FAILED : SUCCESS;
        }
        (*remainder)->sign = (((*remainder)->sign)!= ZERO) ? src2->sign : ZERO;
    }
    else if (((src1->sign == POSITIVE) && (src2->sign == NEGATIVE)) || ((src1->sign == NEGATIVE) && (src2->sign == POSITIVE)))
    {
        temp_src1->sign = temp_src2->sign = POSITIVE;
        if (bi_compare(temp_src1, temp_src2) >= 0)
        {
            error_msg = bi_word_long_division(quotient, remainder, temp_src1, temp_src2);
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



/***********************************************
 * Division
 ***********************************************/
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
msg bi_naive_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2)
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
            error_msg = bi_naive_long_division(quotient, remainder, temp_src1, temp_src2);
        }


        else
        {
            error_msg = (bi_new(quotient, 1) == FAILED || bi_assign(remainder, temp_src1) == FAILED) ? FAILED : SUCCESS;
        }
        (*remainder)->sign = (((*remainder)->sign)!= ZERO) ? src2->sign : ZERO;
    }
    else if (((src1->sign == POSITIVE) && (src2->sign == NEGATIVE)) || ((src1->sign == NEGATIVE) && (src2->sign == POSITIVE)))
    {
        temp_src1->sign = temp_src2->sign = POSITIVE;
        if (bi_compare(temp_src1, temp_src2) >= 0)
        {
            error_msg = bi_naive_long_division(quotient, remainder, temp_src1, temp_src2);
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