#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

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



const int INF_ROOTS = 42;

int main()
{
    printf ("This is quadratic equation solver!\n");
    printf ("Please, input a, b, c\n");

    double a = 0, b = 0, c = 0;
    while (scanf ("%lf %lf %lf", &a, &b, &c) != 3)
        Monkey();

    double x1 = 0, x2 = 0;
    int rootNumber = QuadrSolve (a, b, c, &x1, &x2);

    switch (rootNumber)
    {
        case 0:
            printf ("No roots!\n");
            break;
        case 1:
            printf ("%lf is the only root of the given equation\n", x1);
            break;
        case 2:
            printf ("%lf, %lf are roots of the given equation\n", x1, x2);
            break;
        case INF_ROOTS:
            printf ("Ooh! Infinite number of roots!\n");
            break;
        default:
            printf ("Something went wrong...\n");
    }

    return 0;
}

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



void Monkey()
{
    while (getchar() != '\n');
    printf ("Incorrect input. Please, try again \n");
}

