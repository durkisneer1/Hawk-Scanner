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
void assign();
void ifstmt();
void whilestmt();
void input();
void output();
void expr();
void factor();
void operand();
void num();

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
        if (nextToken != BEGIN)
            declSec();
        match(BEGIN);
        stmtSec();
    }
}

void declSec()
{
    std::cout << "DECL_SEC\n";
    decl();
    if (nextToken != BEGIN)
        declSec();
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
    if (nextToken != END)
        stmtSec();
}

void stmt()
{
    std::cout << "STMT\n";
    switch (nextToken)
    {
    case IDENT:
        assign();
        break;
    case IF:
        ifstmt();
        break;
    case WHILE:
        whilestmt();
        break;
    case INPUT:
        input();
        break;
    case OUTPUT:
        output();
        break;
    }
}

void assign()
{
    std::cout << "ASSIGN\n";
    id();
    if (nextToken == COLON)
    {
        match(COLON);
        if (nextToken == EQUAL_OP)
        {
            match(EQUAL_OP);
            expr();
        }
    }
}

void ifstmt()
{
    std::cout << "IFSTMT\n";
}

void whilestmt()
{
    std::cout << "WHILESTMT\n";
}

void input()
{
    std::cout << "INPUT\n";
}

void output()
{
    std::cout << "OUTPUT\n";
}

void expr()
{
    std::cout << "EXPR\n";
    factor();
}

void factor()
{
    std::cout << "FACTOR\n";
    operand();
}

void operand()
{
    std::cout << "OPERAND\n";
    num();
}

void num()
{
    std::cout << "NUM\n";
}