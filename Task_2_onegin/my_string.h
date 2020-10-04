#include <stdlib.h>


/**
 * @file my_string.h
 *
 * @brief Contains declarations Strlen, Strcmp, Strcat, Strtok
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 10/03/2020
 */


#ifndef TASK_2_ONEGIN_MY_STRING_H
#define TASK_2_ONEGIN_MY_STRING_H

/**
 * This function find length of string
 * @param str
 * @return length of str
 */
size_t Strlen (const char* str);

/**
 * This function compare strings
 * @param s1
 * @param s2
 * @return an integer greater than, equal to, or less than 0, according as the string Fa s1 is greater than, equal to, or less than the string Fa s2
 */
int Strcmp (const char * s1 , const char * s2 );

/**
 * This function concatenate strings
 * @param dest
 * @param src
 * @return functions return the pointer to result string
 */
char* Strcat(char *dest, const char *src);

/**
 * This function isolate sequential tokens in a null-terminated string
 * @param s
 * @param delim
 * @return pointer to the next token
 */
char *Strtok(char *s, const char *delim);


#endif //TASK_2_ONEGIN_MY_STRING_H
