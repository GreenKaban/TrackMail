#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_string.h"


/**
 * @file my_string.c
 *
 * @brief Contains definitions Strlen, Strcmp, Strcat, Strtok
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 10/03/2020
 */



size_t Strlen (const char* str){
    const char* s = str;
    while (*s) s++;
    return s - str;

}




int Strcmp (const char * s1 , const char * s2 ){
    const char* c1 = s1;
    const char* c2 = s2;
    while ((*c1) && (*c2)){
        if (*c1 < *c2){
            return -1;
        }
        if (*c1 > *c2){
            return 1;
        }

        c1++;
        c2++;
    }
    if (!((*c1) || (*c2))) {
        return 0;
    }
    if (!(*c1)){
        return -1;
    }
    if (!(*c2)){
        return 1;
    }
    return 0;

}






char* Strcat(char *dest, const char *src)
{
    size_t dest_len = strlen(dest);
    size_t i = 0;

    for (i = 0 ; src[i] != '\0' ; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';

    return dest;
}




char * Strtok(char *s, const char *delim){
    static char* last;
    static char* first;

    if (s == NULL && first == NULL){
        return NULL;
    }

    if (s!=NULL){
        first = s;
        last = s+Strlen(s);
    } else{
        if (first == last){
            return NULL;
        }
        while (*first&&first!=last){
            first++;
        }

        if (first != last){
            first++;
        }
        if (first == last){
            return NULL;
        }

    }
    const char* d =delim;
    while (*d){
        char* p = first;
        while (p!=last){
            if (*p==*d){
                *p ='\0';
            }
            p++;
        }
        d++;
    }

    return first;
}



