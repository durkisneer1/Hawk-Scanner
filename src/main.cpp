#include <iostream>

#include "Constants.hpp"
#include "Lexical.hpp"

void match(int expectedToken);

void program();
void declSec();
void decl();
void idList();
void id();
void type();
void stmtSec();
void stmt();

LexicalAnalyzer lexical("../front.in");
int nextToken;

int main()
{
    nextToken = lexical.lex();
    program();

    return EXIT_SUCCESS;
}

void match(int expectedToken)
{
    if (nextToken == expectedToken)
        nextToken = lexical.lex();
    else
        std::cerr << "ERROR!\n";
}

void program()
{
    std::cout << "PROGRAM\n";
    if (nextToken == PROGRAM)
    {
        match(PROGRAM);
        declSec();
        if (nextToken == BEGIN)
        {
            match(BEGIN);
            stmtSec();
        }
    }
}

void declSec()
{
    std::cout << "DECL_SEC\n";
    do
    {
        decl();
    } while (nextToken != BEGIN);
}

void decl()
{
    std::cout << "DECL\n";
    idList();
    if (nextToken == COLON)
    {
        match(COLON);
        type();
        if (nextToken == SEMIC)
        {
            match(SEMIC);
        }
    }
}

void idList()
{
    std::cout << "ID_LIST\n";
    id();
    if (nextToken == COMMA)
    {
        match(COMMA);
        idList();
    }
}

void id()
{
    std::cout << "ID\n";
    if (nextToken == IDENT)
    {
        match(IDENT);
    }
}

void type()
{
    std::cout << "TYPE\n";
    if (nextToken == INT_LIT)
    {
        match(INT_LIT);
    }
}

void stmtSec()
{
    std::cout << "STMT_SEC\n";
    stmt();
}

void stmt()
{
    std::cout << "STMT\n";
    
}