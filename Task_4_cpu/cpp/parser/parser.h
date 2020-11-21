/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */
#ifndef TASK_4_CPU_PARSER_H
#define TASK_4_CPU_PARSER_H



#include <cpp/lexer/lexer.h>
#include <cpp/parser/nodes/nodes.h>
#include "ministringutils/ministringutils.h"
#include "logging/logging.h"
#include "utils/error_codes.h"
extern "C"
{
#include "minilog/minilog.h"
#include "minitools/error.h"
}



class Parser
{

private:

    logger* log_;
    Lexer* lexer;
    Token* cur;

public:

    static uint get_arguments_number(CommandType command_type);

    explicit Parser(Lexer* lexer);

    Parser(Lexer* lexer, logger* log_);

    Token* current();

    Token* match_any();

    Token* match(TokenType type);

    bool is_eof();

    Program* get_program();

    Statement* get_statement();

    void read_arguments(Statement* statement);

    Argument* get_numeric_argument();

    Argument* get_register_argument();

    Argument* get_mark_argument();

private:

    char get_numeric_argument_value(Token* token);

    char get_register_argument_value(Token* token);

    void proceed();

};



#endif //TASK_4_CPU_PARSER_H
