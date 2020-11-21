#include <cstdio>
#include <string>
#include "cpp/lexer/lexer.h"
#include "cpp/parser/parser.h"
#include "assembler/assembler.h"
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

static void show_help(const char* command);

static void assembler(string* in_filename, string* out_filename);



int main(int argc, char* argv[])
{
    log_ = lang_logger();
    Info(log_, "\n\n ~ Assembler ~\n");

    string in_filename;
    string out_filename;
    bool help;
    read_console_args(argc, argv, &in_filename, &out_filename, &help);

    if (help)
        show_help(argv[0]);
    else
        assembler(&in_filename, &out_filename);

    Info(log_, "Assembler finished successfully\n");
}



static void show_help(const char* command)
{
    Info(log_, "Help mode");

    printf(" ~ lang assembler ~ \n"
           "Assembles the given program in lang.\n"
           " ~ usage ~ \n"
           "%s\n"
           "%s h,\n"
           "%s help - shows this message\n"
           "%s <in_filename> <out_filename> — assembles the file <in_filename> "
           "and writes the assembley to <out_filename>\n",
           command, command, command, command
    );
}

static void assembler(string* in_filename, string* out_filename)
{
    Info(log_, format(
            "Assembler mode. in_filename = %s, out_filename = %s",
            in_filename->c_str(), out_filename->c_str()
            ).c_str());

    FILE* input = check_open_file(in_filename, "r", log_);
    FILE* output = check_open_file(out_filename, "w", log_);

    Lexer lexer {input, log_};
    Parser parser {&lexer, log_};
    Program* program = parser.get_program();
    Info(log_, "Parsed program");

    assemble(program, output);
    Info(log_, format(
            "Assembled program to %s", out_filename->c_str()
            ).c_str());

    fclose(input);
    fclose(output);
}
