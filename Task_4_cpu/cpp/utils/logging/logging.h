#ifndef TASK_4_CPU_LOGGING_H
#define TASK_4_CPU_LOGGING_H

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

#include <string>
extern "C"
{
#include "minilog/minilog.h"
}
using namespace std;



#ifndef LOG_FILENAME
#define LOG_FILENAME        "log.txt"
#endif
#ifndef LOG_LEVEL
#define LOG_LEVEL           LVL_DEBUG
#endif



logger* lang_logger();

void checked_log(logger* log_, int level, const string& message);



#endif //TASK_4_CPU_LOGGING_H
