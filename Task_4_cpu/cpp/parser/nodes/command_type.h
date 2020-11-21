/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

#ifndef TASK_4_CPU_COMMAND_TYPE_H
#define TASK_4_CPU_COMMAND_TYPE_H



#include <string>
#include <map>
#include "ministringutils/ministringutils.h"
#include "utils/error_codes.h"
extern "C"
{
#include "minitools/error.h"
}
using namespace std;



enum CommandType
{

    invalid = 0,

    // Math
    add = 1,
    sub,
    mul,
    divide,
    power,
    sqrt_,
    mod,

    // Logic
    less = 10,
    more,
    less_eq,
    more_eq,
    eq,
    not_eq_,
    not_,

    // Stack
    push = 20,
    dup,

    // Registers
    put,
    take,

    // IO
    in = 30,
    out,
    out_char,

    // Control flow
    end = 40,
    mark,
    goto_,
    visit,
    back,

};

bool is_valid_command(const string& str);

CommandType get_command_type(const string& str);

string get_command_type_name(CommandType command_type);



#endif //TASK_4_CPU_COMMAND_TYPE_H
