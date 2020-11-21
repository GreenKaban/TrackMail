#include "command_type.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

static map<string, CommandType> command_type_by_string();
static map<CommandType, string> name_by_command_type();



bool is_valid_command(const string& str)
{
    return command_type_by_string().count(str) > 0;
}

CommandType get_command_type(const string& str)
{
    if (command_type_by_string().count(str) == 0)
        return invalid;
    else
        return command_type_by_string().at(str);
}

string get_command_type_name(CommandType command_type)
{
    if (name_by_command_type().count(command_type) == 0)
        ERROR_EXIT_JUST_MES(format("Invalid command type: %d",
                command_type).c_str(), invalid_command)
    else
        return name_by_command_type().at(command_type);
}



static map<string, CommandType> command_type_by_string()
{
    static const std::map<string, CommandType> command_type_by_string =
    {
        // Math
        {"+"  ,     add},
        {"add",     add},
        {"-"  ,     sub},
        {"sub",     sub},
        {"*"  ,     mul},
        {"mul",     mul},
        {"/"  ,     CommandType::divide},
        {"div",     CommandType::divide},
        {"^"  ,     power},
        {"power",   power},
        {"sqrt",    sqrt_},
        {"%"  ,     mod},
        {"mod",     mod},
        // Logic
        {"<"     ,  CommandType::less},
        {"less"  ,  CommandType::less},
        {">"     ,  more},
        {"more"  ,  more},
        {"<="    ,  less_eq},
        {"lesseq",  less_eq},
        {">="    ,  more_eq},
        {"moreeq",  more_eq},
        {"=="    ,  eq},
        {"eq"    ,  eq},
        {"!="    ,  not_eq_},
        {"noteq" ,  not_eq_},
        {"!"     ,  not_},
        {"not"   ,  not_},
        // Stack, registers
        {"push",    push},
        {"dup" ,    dup},
        {"put" ,    put},
        {"take",    take},
        // IO
        {"in"     , in},
        {"out"    , out},
        {"outchar", out_char},
        // Control flow
        {"end",     CommandType::end},
        {"mark",    mark},
        {"goto",    goto_},
        {"visit",   visit},
        {"back",    back},
    };

    return command_type_by_string;
}

static map<CommandType, string> name_by_command_type()
{
    static const std::map<CommandType, string> name_by_command_type =
    {
        // Math
        {add,                 "add"},
        {sub,                 "sub"},
        {mul,                 "mul"},
        {CommandType::divide, "div"},
        {power,               "power"},
        {sqrt_,  "sqrt"},
        {mod,                 "mod"},
        // Logic
        {CommandType::less,   "less"},
        {more,                "more"},
        {less_eq,             "lesseq"},
        {more_eq,             "moreeq"},
        {eq,                  "eq"},
        {not_eq_,             "noteq"},
        {not_,                "not"},
        // Stack, registers
        {push,                "push"},
        {dup,                 "dup"},
        {put,                 "put"},
        {take,                "take"},
        // IO
        {in,                  "in"},
        {out,                 "out"},
        {out_char,            "outchar"},
        // Control flow
        {CommandType ::end,   "end"},
        {mark,                "mark"},
        {goto_,               "goto"},
        {visit,               "visit"},
        {back,                "back"},
    };

    return name_by_command_type;
}
