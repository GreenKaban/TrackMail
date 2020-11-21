#include <cstdio>
#include <string>
#include "parser/nodes/nodes.h"
#include "disassembler/disassembler.h"
#include "console_args/console_args.h"
#include "checked_actions/checked_io.h"
#include "logging/logging.h"
#include "ministringutils/ministringutils.h"
extern "C"
{
#include "minilog/minilog.h"
}
using namespace std;

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

static logger* log_;

void show_help(const char* command);

void disassembler(string* in_filename, string* out_filename);



int main(int argc, char* argv[])
{
    log_ = lang_logger();
    Info(log_, "\n\n ~ Disassembler ~\n");
    
    string in_filename;
    string out_filename;
    bool help;
    read_console_args(argc, argv, &in_filename, &out_filename, &help);

    if (help)
        show_help(argv[0]);
    else
        disassembler(&in_filename, &out_filename);
    
    Info(log_, "Disassembler finished successfully\n");
}



void show_help(const char* command)
{
    Info(log_, "Help mode");
    
    printf(" ~ lang disassembler ~ \n"
           "Disassembles the given program in lang assembley.\n"
           " ~ usage ~ \n"
           "%s\n"
           "%s h,\n"
           "%s help - shows this message\n"
           "%s <in_filename> <out_filename> — disassembles the file "
           "<in_filename> and writes it to <out_filename>\n",
           command, command, command, command
    );
}

void disassembler(string* in_filename, string* out_filename)
{
    Info(log_, format(
            "Disassembler mode. in_filename = %s, out_filename = %s",
            in_filename->c_str(), out_filename->c_str()
            ).c_str());

    FILE* input = check_open_file(in_filename, "r", log_);
    FILE* output = check_open_file(out_filename, "w", log_);

    Program* program = disassemble(input);
    Info(log_, "Disassembled program");
    
    write_source(program, output);
    Info(log_, format(
            "Wrote disassembled source to %s", out_filename
            ).c_str());

    fclose(input);
    fclose(output);
}
