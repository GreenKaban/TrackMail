/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

#ifndef TASK_4_CPU_EXECUTOR_H
#define TASK_4_CPU_EXECUTOR_H



#include <cstdio>
#include <cmath>
#include <stack>
#include <map>
#include "cpp/parser/nodes/nodes.h"
#include "utils/error_codes.h"
#include "utils/logging/logging.h"
#include "ministringutils/ministringutils.h"
extern "C"
{
#include "minilog/minilog.h"
#include "minitools/error.h"
}



enum StatementResult
{
    ok,
    error_,
    finish
};


class Executor
{

private:

    static constexpr int n_registers = 'z' - 'a';
    logger* log_;
    Program* program;
    stack<char> stack_;
    map<string, uint> marks;
    stack<uint> back_positions;
    char registers[n_registers]{};

public:

    explicit Executor(Program* program);

    Executor(Program* program, logger* log_);

    void execute();

private:

    void collect_marks();

    StatementResult execute_statement(Statement* statement, ulong& i);

    StatementResult execute_binary_command(CommandType command_type);

};



#endif //TASK_4_CPU_EXECUTOR_H
