#include <cstdio>
#include <string>
#include "cpp/lexer/lexer.h"
#include "cpp/parser/parser.h"
#include "cpp/executor/executor.h"
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

void interpreter(string* filename);



int main(int argc, char* argv[])
{
    log_ = lang_logger();
    Info(log_, "\n\n ~ Interpreter ~\n");

    string filename;
    bool help;
    read_console_args(argc, argv, &filename, &help);

    if (help)
        show_help(argv[0]);
    else
        interpreter(&filename);

    Info(log_, "Interpreter finished successfully\n");
}



void show_help(const char* command)
{
    Info(log_, "Help mode");

    printf(" ~ lang interpreter ~ \n"
           "Interprets the given program in lang.\n"
           " ~ usage ~ \n"
           "%s\n"
           "%s h,\n"
           "%s help - shows this message\n"
           "%s <filename> — interprets the file <filename>\n",
           command, command, command, command
    );
}

void interpreter(string* filename)
{
    Info(log_, format(
            "Interpreter mode. filename = %s",
            filename->c_str(), filename->c_str()
            ).c_str());

    FILE* input = check_open_file(filename, "r", log_);

    Lexer lexer{input, log_};
    Parser parser{&lexer, log_};
    Program *program = parser.get_program();
    Info(log_, "Parsed program");

    Executor executor{program, log_};
    executor.execute();
    Info(log_, "Executed program");

    fclose(input);
}