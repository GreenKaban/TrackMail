/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

#ifndef TASK_4_CPU_CHECKED_IO_H
#define TASK_4_CPU_CHECKED_IO_H



#include <cstdio>
#include <string>
#include "cpp/utils/error_codes.h"
#include "ministringutils/ministringutils.h"
extern "C"
{
#include "minitools/error.h"
#include "minilog/minilog.h"
}
using namespace std;



FILE* check_open_file(string* filename, const string& mode, logger* log);



#endif //TASK_4_CPU_CHECKED_IO_H
