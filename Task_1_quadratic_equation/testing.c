#include "quadr_solve.h"
#include "testing.h"

/**
 * @file testing.c
 *
 * @brief Contains definitions of functions for for testing quadratic solver
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 9/21/2020
 */



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