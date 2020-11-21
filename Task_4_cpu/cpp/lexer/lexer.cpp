#include "lexer.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

// Public functions



Lexer::Lexer(FILE* input) : Lexer(input, nullptr) {}

Lexer::Lexer(FILE* input, logger* log_)
{
    assert(input != nullptr);

    this->log_ = log_;
    this->input = input;
    this->cur = UNINITIALIZED_LEXER_CUR;
    this->line = 1;
    this->symbol = 0;

    checked_log(log_, LVL_DEBUG, "Lexer: constructed");
}

int Lexer::current()
{
    if (cur == UNINITIALIZED_LEXER_CUR)
        proceed();

    return cur;
}

int Lexer::match_any()
{
    int prev = current();
    proceed();

    return prev;
}

int Lexer::match(int c)
{
    int prev = current();
    if (prev != c)
        ERROR_EXIT_JUST_MES(format(
                "Mismatched character at %d:%d. expected '%c', got '%c'",
                line, symbol, c, prev).c_str(),
                mismatched_character);
    proceed();

    return prev;
}

bool Lexer::is_eof()
{
    return current() == EOF;
}

Token* Lexer::get_token()
{
    checked_log(log_, LVL_DEBUG_2, "Lexer: get_token()");

    while (!is_eof())
    {
        switch (current())
        {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                skip_ws();
                break;
            case '#':
                skip_comment();
                break;
            case '\'':
                return get_character();
            default:
                if (is_digit(current()))
                    return get_number();
                else if (is_letter(current()))
                    return get_identifier();
                else
                    ERROR_EXIT_JUST_MES(format(
                            "Unexpected character '%c' at %d:%d",
                            current(), line, symbol).c_str(),
                            unexpected_character);
        }
    }

    checked_log(log_, LVL_DEBUG, "Lexer: reached EOF");
    return new Token(eof, "", line, symbol);
}



// Private functions



void Lexer::proceed()
{
    assert(input != nullptr);

    cur = fgetc(this->input);
    symbol += 1;

    if (cur == '\n')
    {
        line += 1;
        symbol = 0;
    }
}

bool Lexer::is_ws(int c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool Lexer::is_digit(int c)
{
    return c >= '0' && c <= '9';
}

bool Lexer::is_letter(int c)
{
    switch(c)
    {
        case '_':
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
        case '<':
        case '>':
        case '=':
        case '!':
            return true;
        default:
            return (c >= 'a' && c <= 'z')
                   || (c >= 'A' && c <= 'Z');
    }
}

void Lexer::skip_ws()
{
    while (is_ws(current()))
        match_any();
}

void Lexer::skip_comment()
{
    match('#');
    while (current() != '\n')
        match_any();
}

Token* Lexer::get_character()
{
    uint start_line = line;
    uint start_symbol = symbol;

    match('\'');
    int c = match_any();
    if (c == EOF)
        ERROR_EXIT_JUST_MES(format("Unexpected EOF character at %d:%d",
                start_line, start_symbol).c_str(), unexpected_character);
    match('\'');

    string value {'\'', (char)c, '\''};

    checked_log(log_, LVL_DEBUG_2, format(
            "Lexer: got token: character %s %d:%d",
            value.c_str(), start_line, start_symbol));
    return new Token(character, value, start_line, start_symbol);
}

Token *Lexer::get_number()
{
    uint start_line = line;
    uint start_symbol = symbol;

    string value;
    while (is_digit(current()))
        value += (char)match_any();

    checked_log(log_, LVL_DEBUG_2, format(
            "Lexer: got token: number %s %d:%d",
            value.c_str(), start_line, start_symbol));
    return new Token(number, value, start_line, start_symbol);
}

Token* Lexer::get_identifier()
{
    uint start_line = line;
    uint start_symbol = symbol;

    string value;
    if (is_letter(current()))
        value += (char)match_any();
    else
        ERROR_EXIT_JUST_MES(format(
                "Unexpected character at %d:%d. Expected a letter, got '%c'",
                start_line, start_symbol, current()).c_str(),
                unexpected_character);
    while (is_letter(current()) || is_digit(current()))
        value += (char)match_any();

    checked_log(log_, LVL_DEBUG_2, format(
            "Lexer: got token: identifier %s %d:%d",
            value.c_str(), start_line, start_symbol));
    return new Token(identifier, value, start_line, start_symbol);
}
