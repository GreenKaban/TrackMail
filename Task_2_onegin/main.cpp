#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <clocale>
#include "sorter.h"
#include "tester.h"
#include "converter.h"


/**
 * @file main.cpp
 *
 * @brief Program for sorting Onegin
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 10/17/2020
 */


int main()
{
#ifdef NDEBUG
    TestingCompareWstr();
    TestingConverter();
#endif
    SortFromFile("origin.txt", "remake1.txt", Direct);
    SortFromFile("origin.txt", "remake2.txt", Inverse);

    return 0;
}