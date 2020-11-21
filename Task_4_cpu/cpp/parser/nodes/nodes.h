
/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */
#ifndef TASK_4_CPU_NODES_H
#define TASK_4_CPU_NODES_H



#include <vector>
#include "lexer/token/token.h"
#include "parser/nodes/command_type.h"
using namespace std;



class Program;

class Statement;

class Argument;



class Program
{

public:

    vector<Statement*> statements;

    Program();

};

class Statement
{

public:

    Token* command;
    CommandType command_type;
    vector<Argument*> arguments;

    Statement(Token* command, CommandType command_type);

};

class Argument
{

public:

    Token* token;
    char value;

    Argument(Token* token, char value);

};


#endif //TASK_4_CPU_NODES_H
