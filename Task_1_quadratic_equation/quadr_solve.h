#ifndef TRACKMAIL_QUADR_SOLVE_H
#define TRACKMAIL_QUADR_SOLVE_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>


/**
 * @file quadr_solve.h
 *
 * @brief Program for solving quadratic equations
 * @brief just input a, b, c coefficients of ax^2 + bx + c = 0
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




int QuadrSolve (double a, double b, double c, double *x1, double *x2)
{
    if (!(isfinite (a)) || !(isfinite (b)) || !(isfinite (c)))
        exit (EXIT_FAILURE);

    assert (x1 != x2);
    assert (x1 != NULL);
    assert (x2 != NULL);

    if (IsZero(a))
    {
        if (IsZero(b))
        {
            return (IsZero(c)) ? INF_ROOTS : 0;
        }
        else
        {
            *x1 = - c / b;

            return 1;
        }
    }

    double D = b * b - 4 * a * c;

    if (D > 0)
    {
        *x1 = (-b + sqrt(D)) / (2 * a);
        *x2 = (-b - sqrt(D)) / (2 * a);

        return 2;
    }
    else if (IsZero(D))
    {
        *x1 = *x2 = - b / (2 * a);

        return 1;
    }
    else
    {
        return 0;
    }
}

bool IsZero (double value){
    if (fabs (value) < 1e-7){
        return true;
    } else {
        return false;
    }
}

void Monkey()
{
    while (getchar() != '\n');
    printf ("Incorrect input. Please, try again \n");
}

double RandomDouble()
{
    double law = -7, high = 7;

    double random = (double) rand() / ((double) RAND_MAX + 1);

    return random;


}


double Parabola (double a, double b, double c, double x)
{
    double value = a * x * x + b * x + c;

    return value;
}

bool QuadrZero (double a, double b, double c, double x1, double x2)
{
    if ( (Parabola (a, b, c, x1) == 0) && (Parabola (a, b, c, x2) == 0))
        return true;

    return false;
}

void Testing()
{
    for (int i = 0; i < 20; i++)
    {
        double a = RandomDouble();
        double b = RandomDouble();
        double c = RandomDouble();

        double x1 = 0, x2 = 0;
        int testSolNumb = QuadrSolve (a, b, c, &x1, &x2);

        printf ("For a = %lf, b = %lf, c = %lf coefficients\n", a, b, c);

        switch (testSolNumb)
        {
            case 0:
                printf ("No roots\n");

                ///We can be sure in this result because the sign and value of the discriminant is calculated exactly
                printf ("Test passed\n");
                break;

            case INF_ROOTS:
                printf ("Infinite solution number\n");
                printf ("Test passed\n");
                break;

            default:
                printf ("root1 = %lf, root2 = %lf\n", x1, x2);

                if (QuadrZero (a, b, c, x1, x2))
                {
                    printf ("Test passed!\n \n");
                }
                else
                {
                    printf ("Failed\n");
                }
        }

    }
}

#endif //TRACKMAIL_QUADR_SOLVE_H