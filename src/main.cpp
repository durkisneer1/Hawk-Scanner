#include <iostream>

#include "Constants.hpp"
#include "Lexical.hpp"

void expr();
void term();
void factor();

LexicalAnalyzer lexical("../front.in");
int nextToken;

int main()
{
    nextToken = lexical.lex();
    expr();

    return EXIT_SUCCESS;
}

void expr()
{
    std::cout << "Enter <expr>\n";
    term();
    while (nextToken == ADD_OP || nextToken == SUB_OP)
    {
        nextToken = lexical.lex();
        term();
    }
    std::cout << "Exit <expr>\n";
}

void term()
{
    std::cout << "Enter <term>\n";
    factor();
    while (nextToken == MULT_OP || nextToken == DIV_OP)
    {
        nextToken = lexical.lex();
        factor();
    }
    std::cout << "Exit <term>\n";
}

void factor()
{
    std::cout << "Enter <factor>\n";
    if (nextToken == IDENT || nextToken == INT_LIT)
        nextToken = lexical.lex();
    else
    {
        if (nextToken == LEFT_PAREN)
        {
            nextToken = lexical.lex();
            expr();
            if (nextToken == RIGHT_PAREN)
                nextToken = lexical.lex();
            else
                std::cerr << "Error: Expected ')'\n";
        }
        else
        {
            std::cerr << "Error: Expected '(', identifier, or integer literal\n";
        }
    }
    std::cout << "Exit <factor>\n";
}