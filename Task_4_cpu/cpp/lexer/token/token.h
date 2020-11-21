#ifndef TASK_4_CPU_TOKEN_H
#define TASK_4_CPU_TOKEN_H

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

#include <string>
#include "minitools/minitypes.h"
using namespace std;



enum TokenType
{
    eof,
    character,
    number,
    identifier
};

string token_type_name();



class Token
{

public:

    TokenType type;
    string value;
    uint line;
    uint symbol;

    Token(TokenType type, string value, uint line, uint symbol);

};



#endif //TASK_4_CPU_TOKEN_H
