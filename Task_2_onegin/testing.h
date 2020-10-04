

/**
 * @file testing.h
 *
 * @brief Contains declarations of functions for for testing Strlen, Strcmp, Strcat, Strtok
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 10/03/2020
 */

#ifndef TASK_2_ONEGIN_TESTING_H
#define TASK_2_ONEGIN_TESTING_H


#define TEST_ARRAY_SIZE 8

#define TEST_ARRAY  \
char* a[8];          \
a[0]="\n";            \
a[1] = "qwew";         \
a[2] = "wqeweq\neqeqe"; \
a[3] = "\0";             \
a[4] = "qwewwqe\0qweq";   \
a[5] = "abc";              \
a[6] = "abc";               \
a[7] = "";                   \


/**
 * This function tests the Strlen function from my_string.h
 * @return number of errors
 */
int StrlenTest();

/**
 * This function tests the Strcmp function from my_string.h
 * @return number of errors
 */
int StrcmpTest();

/**
 * This function tests the Strcat function from my_string.h
 * @return number of errors
 */
int StrcatTest();

/**
 * This function tests the Strtok function from my_string.h
 * @return number of errors
 */
int StrtokTest();

/**
 * This function starts testing functions from my_string.h
 */
void TestAll();

#endif //TASK_2_ONEGIN_TESTING_H
