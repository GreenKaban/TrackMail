/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

#ifndef TASK_4_CPU_ERROR_CODES_H
#define TASK_4_CPU_ERROR_CODES_H



enum ErrorCode
{
    file_open_error,
    statement_execution_error,
    invalid_command,
    mismatched_character,
    unexpected_character,
    mismatched_token,
    unexpected_token_value,
    unexpected_token,
    invalid_register,
    invalid_mark,
    unexpected_argument
};



#endif //TASK_4_CPU_ERROR_CODES_H
