#include "parser.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

// Public functions



uint Parser::get_arguments_number(CommandType command_type)
{
    switch(command_type)
    {
        case push:
            return 1;
        default:
            return 0;
    }
}

Parser::Parser(Lexer* lexer) : Parser(lexer, nullptr) {}

Parser::Parser(Lexer* lexer, logger* log_)
{
    assert(lexer != nullptr);

    this->log_ = log_;
    this->lexer = lexer;
    this->cur = nullptr;

    checked_log(log_, LVL_DEBUG, "Parser: constructed");
}

Token* Parser::current()
{
    if (cur == nullptr)
        proceed();

    return cur;
}

Token* Parser::match_any()
{
    Token* c = current();
    proceed();

    return c;
}

Token* Parser::match(TokenType type)
{
    Token* c = current();
    if (c->type != type)
    {
        string message = format(
                "Mismatched token at %d:%d. Expected %d, got %d",
                c->line, c->symbol, type, c->type);
        checked_log(log_, LVL_ERROR, message);
        ERROR_EXIT_JUST_MES(message.c_str(), mismatched_token);
    }
    proceed();

    return c;
}

bool Parser::is_eof()
{
    return current()->type == eof;
}

Program* Parser::get_program()
{
    checked_log(log_, LVL_DEBUG_2, "Parser: get_program()");

    Program* program = new Program();

    while (!is_eof())
        program->statements.push_back(get_statement());

    checked_log(log_, LVL_DEBUG_2, "Parser: got program");
    return program;
}

Statement* Parser::get_statement()
{
    checked_log(log_, LVL_DEBUG_2, "Parser: get_statement()");

    Token* command = match(identifier);
    CommandType command_type = get_command_type(command->value);
    if (command_type == invalid)
    {
        string message = format("Invalid command '%s' at %d:%d",
                command->value.c_str(), command->line, command->symbol);
        checked_log(log_, LVL_ERROR, message);
        ERROR_EXIT_JUST_MES(message.c_str(), unexpected_token);
    }

    Statement* statement = new Statement(command, command_type);
    read_arguments(statement);

    checked_log(log_, LVL_DEBUG_2, format(
            "Parser: got statement; command = %s", command->value.c_str()));
    return statement;
}

void Parser::read_arguments(Statement* statement)
{
    switch (statement->command_type)
    {
        case push:
            statement->arguments.push_back(get_numeric_argument());
            break;
        case put:
        case take:
            statement->arguments.push_back(get_register_argument());
            break;
        case mark:
        case goto_:
        case visit:
            statement->arguments.push_back(get_mark_argument());
            break;
        default:
            break;
    }
}

Argument* Parser::get_numeric_argument()
{
    Token* token = match_any();
    assert(token->type == character || token->type == number);
    char value = get_numeric_argument_value(token);

    return new Argument(token, value);
}

Argument* Parser::get_register_argument()
{
    Token* token = match_any();
    assert(token->type == identifier);
    char value = get_register_argument_value(token);

    return new Argument(token, value);
}

Argument* Parser::get_mark_argument()
{
    Token* token = match_any();
    assert(token->type == identifier);
    char value = 0;

    return new Argument(token, value);
}



// Private functions



char Parser::get_numeric_argument_value(Token* token)
{
    if (token->type == character)
        return token->value[1];
    else if (token->type == number)
    {
        int val = stoi(token->value);
        if (val < 0 || val > 255)
        {
            string message = format(
                    "Unexpected numeric argument value: %d at %d:%d",
                    val, token->line, token->symbol);
            checked_log(log_, LVL_ERROR, message);
            ERROR_EXIT_JUST_MES(message.c_str(), unexpected_token_value);
        }
        return (char)val;
    }
    else
    {
        string message = format("Unexpected token type at %d:%d. "
                "Expected character or number, got identifier",
                token->line, token->symbol);
        checked_log(log_, LVL_ERROR, message);
        ERROR_EXIT_JUST_MES(message.c_str(), unexpected_token);
    }
}

char Parser::get_register_argument_value(Token *token)
{
    if (token->type == identifier)
    {
        if (token->value.length() != 1)
        {
            string message = format("Invalid register identifier at %d:%d. "
                    "Expected identifier of length 1, got '%s'",
                    token->line, token->symbol, token->value.c_str());
            checked_log(log_, LVL_ERROR, message);
            ERROR_EXIT_JUST_MES(message.c_str(), invalid_register);
        }
        assert(token->value.length() == 1);
        char c = token->value[0];
        if (c >= 'a' && c <= 'z')
            return (char)(c - 'a');
        else if (c >= 'A' && c <= 'Z')
            return (char)(c - 'A');
        else
        {
            string message = format("Invalid register identifier at %d:%d. "
                    "Expected 'a'-'z' or 'A'-'Z', got %c",
                    token->line, token->symbol, c);
            checked_log(log_, LVL_ERROR, message);
            ERROR_EXIT_JUST_MES(message.c_str(), invalid_register);
        }
    }
    else
    {
        string message = format("Invalid register argument token type at "
                                "%d:%d. Expected identifier, got %d",
                                token->line, token->symbol, token->type);
        checked_log(log_, LVL_ERROR, message);
        ERROR_EXIT_JUST_MES(message.c_str(), unexpected_token);
    }
}

void Parser::proceed()
{
    assert(lexer != nullptr);

    cur = lexer->get_token();
}
