#include "checked_io.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

FILE* check_open_file(string* filename, const string& mode, logger* log)
{
    FILE* file = fopen(filename->c_str(), mode.c_str());

    if (file == nullptr)
    {
        const char* message = format(
                "Failed to open file %s in mode %s",
                filename->c_str(), mode.c_str()).c_str();
        Fatal(log, message);
        ERROR_EXIT_JUST_MES(message, ErrorCode::file_open_error);
    }

    return file;
}
