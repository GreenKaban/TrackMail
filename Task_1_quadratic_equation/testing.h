
#ifndef TASK_1_QUADRATIC_EQUATION_TESTING_H
#define TASK_1_QUADRATIC_EQUATION_TESTING_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>


/**
 * @file testing.h
 *
 * @brief Contains declarations of functions for testing quadratic solver
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 9/21/2020
 */


/**
 * This function is for simple unit testing.
 * Algorithm: solves 15 pseudo-random generated quadratic equation using our program.
 * And compares rightness of resulting roots.
 */
void Testing();


/**
 * Function for generating random double coefficients for test equations.
 * Taken from Eric Roberts' "The Art and Science of C"
 */
double RandomDouble();


/**
 * With given coefficients a, b, c and roots x1, x2 checks the rightness of ax^2 + bx + c = 0 solution
 *
 * @param [in] a a-coefficient
 * @param [in] b b-coefficient
 * @param [in] c c-coefficient
 *
 * @param [in] x1 root for check
 * @param [in] x2 root for check
 *
 * @return true if x1, x2 are roots, false in an another case
 */
bool QuadrZero (double a, double b, double c, double x1, double x2);



/**
 * This function calculates the value of quadratic function ax^2 + bx + c
 * with given coefficients and in the given point
 *
 * @param [in] a a-coefficient
 * @param [in] b b-coefficient
 * @param [in] c c-coefficient
 *
 * @param [in] x some R value
 *
 * @returns ax^2 + bx + c
 */
double Parabola (double a, double b, double c, double x);





/**
 * This function takes tests from a file
 *
 * @param name
 */
void TestingFromFile(char* name);


/**
 *
 * This function checks the solution of a single equation
 *
 * @param a
 * @param b
 * @param c
 */
void TestOne (double a, double b, double c);

#endif //TASK_1_QUADRATIC_EQUATION_TESTING_H
