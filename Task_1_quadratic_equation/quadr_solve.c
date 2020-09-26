

#include "quadr_solve.h"
#include "testing.h"

/**
 * @file quadr_solve.c
 *
 * @brief Contains definitions of functions for solving quadratic equations and auxiliary functions
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

    Normalize(&a, &b, &c);

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



int Normalize (double *a, double *b, double *c){
    double min = fmin(fmin(*a, *b), *c);
    int ex_min = 0;
    frexp (min , &ex_min);
    if (ex_min>-23) {
        return 1;
    }
    int ex_max = 0;
    double max = fmax(fmax(*a, *b), *c);
    frexp (max , &ex_max);

    if (1023-ex_max > -22 - ex_min){

        int p = -22 - ex_min;
        *a = ldexp(*a, p);
        *b = ldexp(*b, p);
        *c = ldexp(*c, p);
        return 0;
    }

//    printf("%lg %lg %lg", *a, *b, *c);


    return 1;
}



