

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

double RandomDouble()
{
    double law = -7, high = 7;

    double random = (double) rand() / ((double) RAND_MAX + 1);

    return random;


}


double Parabola (double a, double b, double c, double x)
{
//    Normalize(&a, &b, &c);

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

       TestOne(a, b, c);

    }
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



void TestingFromFile( char* name){
    FILE *in = fopen(name, "r");
    double a = 0,  b = 0, c =0;

    if (in != NULL) {
        while ( !feof(in)){
            fscanf(in, "%lg %lg %lg", &a, &b, &c);
            TestOne(a, b, c);

        }
//        printf("%lg %lg %lg", a, b, c);
    } else{
        printf("%s %s %s ""file", name, "dont open\n");
    }

    fclose(in);


}


void TestOne (double a, double b, double c){
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