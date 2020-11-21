/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */
#ifndef TASK_4_CPU_CONSOLE_ARGS_H
#define TASK_4_CPU_CONSOLE_ARGS_H



#include <string>
#include <cassert>
#include <cstring>
#include "ministringutils/ministringutils.h"
using namespace std;



void read_console_args(int argc, char* argv[], string* filename, bool* help);

void read_console_args(int argc, char* argv[], string* in_filename,
                       string* out_filename, bool* help);



#endif //TASK_4_CPU_CONSOLE_ARGS_H
