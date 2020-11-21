#include "token.h"

/**
 * @file from Tack_4_cpu
 *
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 11/21/2020
 */

Token::Token(TokenType type, string value, uint line, uint symbol)
{
    this->type = type;
    this->value = value;
    this->line = line;
    this->symbol = symbol;
}
