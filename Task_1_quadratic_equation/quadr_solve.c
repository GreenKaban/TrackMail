#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "quadr_solve.h"

/**
 * @file quadr_solve.c
 *
 * @brief Program for solving quadratic equations
 * @brief just input a, b, c coefficients of ax^2 + bx + c = 0
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 9/21/2020
 */



int QuadrSolve (double a, double b, double c, double *x1, double *x2)
{
    if (!(isfinite (a)) || !(isfinite (b)) || !(isfinite (c)))
        exit (EXIT_FAILURE);

    assert (x1 != x2);
    assert (x1 != NULL);
    assert (x2 != NULL);

    if (a == 0)
    {
        if (b == 0)
        {
            return (c == 0) ? INF_ROOTS : 0;
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
    else if (D == 0)
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

