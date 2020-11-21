#include "logging.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

logger* lang_logger()
{
    logger* log_ = get_logger(
            LOG_FILENAME, false, LOG_LEVEL, false);
    log_->source_position = false;
    return log_;
}

void checked_log(logger* log_, int level, const string& message)
{
    if (log_ != nullptr)
        Log(log_, message.c_str(), level);
}
