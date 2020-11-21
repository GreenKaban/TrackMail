#include "nodes.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

Program::Program() = default;

Statement::Statement(Token* command, CommandType command_type)
{
    this->command = command;
    this->command_type = command_type;
}

Argument::Argument(Token* token, char value)
{
    this->token = token;
    this->value = value;
}
