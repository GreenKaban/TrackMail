#include "disassembler.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

Program* disassemble(FILE* input)
{
    Program* program = new Program();
    for (int inp = fgetc(input); inp != EOF; inp = fgetc(input))
    {
        CommandType c = (CommandType)inp;
        Statement* statement = new Statement(nullptr, (CommandType)c);
        for (uint i = 0; i < Parser::get_arguments_number(c); ++i)
        {
            inp = fgetc(input);
            assert(inp != EOF);
            Argument* argument = new Argument(nullptr, (char)inp);
            statement->arguments.push_back(argument);
        }
        program->statements.push_back(statement);
    }
    return program;
}

void write_source(Program* program, FILE* output)
{
    for (Statement* statement : program->statements)
    {
        string command_name = get_command_type_name(statement->command_type);
        fprintf(output, "%s ", command_name.c_str());
        for (Argument* argument : statement->arguments)
            fprintf(output, "%d ", argument->value);
        fprintf(output, "\n");
    }
}
