/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

#ifndef TASK_4_CPU_LEXER_H
#define TASK_4_CPU_LEXER_H



#include <cstdio>
#include <cassert>
#include "lexer/token/token.h"
#include "minitools/minitypes.h"
#include "ministringutils/ministringutils.h"
#include "logging/logging.h"
#include "utils/error_codes.h"
extern "C"
{
#include "minilog/minilog.h"
#include "minitools/error.h"
}



#define UNINITIALIZED_LEXER_CUR     -2



class Lexer
{

private:

    logger* log_;
    FILE* input;
    int cur;
    uint line;
    uint symbol;

public:

    explicit Lexer(FILE* input);

    Lexer(FILE* input, logger* log_);

    int current();

    int match_any();

    int match(int c);

    bool is_eof();

    Token* get_token();

private:

    static bool is_ws(int c);

    static bool is_digit(int c);

    static bool is_letter(int c);

    void proceed();

    void skip_ws();

    void skip_comment();

    Token* get_character();

    Token* get_number();

    Token* get_identifier();

};



#endif //TASK_4_CPU_LEXER_H
