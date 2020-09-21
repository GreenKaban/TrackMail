#include <cstdio>
#include "quadr_solve.h"

/**
 * @file main.c
 *
 * @brief Program for solving quadratic equations
 * @brief just input a, b, c coefficients of ax^2 + bx + c = 0
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 9/21/2020
 */

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