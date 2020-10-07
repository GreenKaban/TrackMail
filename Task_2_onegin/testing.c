#include "testing.h"
#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * @file testing.c
 *
 * @brief Contains definitions of functions for for testing Strlen, Strcmp, Strcat, Strtok
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 10/03/2020
 */




int StrcatTest() {

    int mistakes = 0;
    TEST_ARRAY
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        for (int j = 0; i < 8; i++) {

            char *dest1 = malloc(30 * sizeof(char));
            char *dest2 = malloc(30 * sizeof(char));
            strcpy(dest1, a[j]);
            strcpy(dest2, a[j]);

            char *r1 = Strcat(dest1, a[i]);
            char *r2 = strcat(dest2, a[i]);
            if (strcmp(r1, r2)) {
                mistakes++;
                printf("strings: \"%s\" and \"%s\"; %s != %s\n", a[j], a[i], Strcat(a[j], a[i]), strcat(a[j], a[i]));

            }
            free(dest1);
            free(dest2);

        }
    }
    return mistakes;


}


int StrcmpTest() {
    int mistakes = 0;
    TEST_ARRAY
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        for (int j = 0; i < 8; i++) {
            int r1 = Strcmp(a[j], a[i]), r2 = strcmp(a[j], a[i]);
            if (r1 != r2) {
                mistakes++;
                printf("string: \"%s\" and \"%s\"; %d != %d\n", a[j], a[i], r1, r2);

            }

        }
    }
    return mistakes;
}

int StrlenTest() {
    int mistakes = 0;
    TEST_ARRAY
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
        long long int r1 = Strlen(a[i]), r2 = strlen(a[i]);
        if (r1 != r2) {
            mistakes++;
            printf("string: \"%s\"; %lld != %lld\n", a[i], r1, r2);

        }

    }
    return mistakes;
}

int StrtokTest () {
    int mistakes = 0;

    char *str[4];
    str[0] = "qwewe.wqew.eqweq";
    str[1] = "qwewe.wq,ew.eqw,eq";
    str[2] = "qwewe.wq,ew.eqw,eq\n";
    str[3] = "qwwqeewe.wqeqq,ewq\new.eqqwew,ewqeqq\n";
    char *delim[3];
    delim[0] = ".";
    delim[1] = ".,";
    delim[2] = ",.\n";

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            char *dest1 = malloc(30 * sizeof(char));
            char *dest2 = malloc(30 * sizeof(char));
            strcpy(dest1, str[i]);
            strcpy(dest2, str[i]);
            char *pch1 = strtok(dest1, delim[j]);
            char *pch2 = Strtok(dest2, delim[j]);

            while (pch1 != NULL || pch2 != NULL) {
                if (strcmp(pch1, pch2) != 0) {
                    printf("strings: \"%s\" \"%s\" not eqval\n", pch1, pch2);
                    mistakes++;
                }
                pch1 = strtok(NULL, delim[j]);
                pch2 = Strtok(NULL, delim[j]);
            }

            free(dest1);
            free(dest2);

        }
    }


    return mistakes;
}



void TestAll() {
    if (!StrlenTest()) {
        printf("%s", "StrlenTest OK\n");
    }
    if (!StrcmpTest()) {
        printf("%s", "StrcmpTest OK\n");
    }
    if (!StrcatTest()) {
        printf("%s", "StrcatTest OK\n");
    }
    if (!StrtokTest()) {
        printf("%s", "StrtokTest OK\n");
    }
}