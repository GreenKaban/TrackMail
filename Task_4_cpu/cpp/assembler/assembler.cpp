#include "assembler.h"


/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */



void assemble(Program* program, FILE* output)
{
    for (Statement* statement : program->statements)
    {
        fprintf(output, "%c", statement->command_type);
        for (Argument* argument : statement->arguments)
            fprintf(output, "%c", argument->value);
    }
}
