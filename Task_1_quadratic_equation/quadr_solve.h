#ifndef TRACKMAIL_QUADR_SOLVE_H
#define TRACKMAIL_QUADR_SOLVE_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>


/**
 * @file quadr_solve.h
 *
 * @brief Contains declarations of functions for solving quadratic equations and auxiliary functions
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 9/21/2020
 */



#define INF_ROOTS 42



/**
 * This method determines user IQ by checking the correctness of input data.
 *
 * @note In a case of failure you will be asked to take part in retake.
 */
void Monkey();



/**
 * This function solves quadratic equation and returns its roots number
 *
 * @param [in]  a a-coeff
 * @param [in]  b b-coeff
 * @param [in]  c c-coeff
 *
 * @param [out] x1 Pointer to the first root
 * @param [out] x2 Pointer to the second root
 *
 * @return Number of solutions
 *
 * @note If solution number is not finite returns INF_ROOTS
 */
int QuadrSolve (double a, double b, double c, double *x1, double *x2);


/**
 * This function is used to compare double to zero with precision
 *
 * @param value
 * @note the accuracy of 1e-7
 * @return return true if value equals 0, false in an another case
 */
bool IsZero (double value);


/**
 * This function normalizes a triple of numbers
 *
 * @param a
 * @param b
 * @param c
 * @return 0 if normalization has occurred, otherwise 1
 */
int Normalize (double *a, double *b, double *c);






#endif //TRACKMAIL_QUADR_SOLVE_H