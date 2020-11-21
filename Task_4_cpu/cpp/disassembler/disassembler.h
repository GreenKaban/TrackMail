/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

#ifndef TASK_4_CPU_DISASSEMBLER_H
#define TASK_4_CPU_DISASSEMBLER_H



#include <cstdio>
#include "parser/parser.h"
#include "parser/nodes/nodes.h"



Program* disassemble(FILE* input);

void write_source(Program* program, FILE* output);



#endif //TASK_4_CPU_DISASSEMBLER_H
