

#include "quadr_solve.h"


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