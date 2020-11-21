#include "console_args.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

static bool is_help(char* arg);



void read_console_args(int argc, char* argv[], string* filename, bool* help)
{
    assert(argc > 0);
    assert(argv != nullptr);
    assert(filename != nullptr);
    assert(help != nullptr);

    *filename = "";
    *help = false;

    switch (argc)
    {
        case 2:
            if (is_help(argv[1]))
                *help = true;
            else
                *filename = argv[1];
            break;
        default:
            *help = true;
    }
}

void read_console_args(int argc, char* argv[], string* in_filename,
        string* out_filename, bool* help)
{
    assert(argc > 0);
    assert(argv != nullptr);
    assert(in_filename != nullptr);
    assert(out_filename != nullptr);
    assert(help != nullptr);

    *in_filename = "";
    *out_filename = "";
    *help = false;

    switch (argc)
    {
        case 3:
            *in_filename = argv[1];
            *out_filename = argv[2];
            break;
        default:
            *help = true;
    }
}



static bool is_help(char* arg)
{
    assert(arg != nullptr);

    return equals(arg, "help") || equals(arg, "h");
}
