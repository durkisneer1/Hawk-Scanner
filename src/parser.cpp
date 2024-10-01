#include <iostream>
#include <fmt/format.h>

#include "Parser.hpp"
#include "Lexer.hpp"
#include "Constants.hpp"

Parser::Parser(Lexer *lexer)
    : lexer(lexer), nextToken(lexer->lex()) {}

bool Parser::accept(int token)
{
    if (nextToken == token)
    {
        lexer->passed();
        nextToken = lexer->lex();
        return true;
    }
    return false;
}

bool Parser::expect(int token)
{
    static const char *tokenNames[] = {
        "program",
        ":",
        ";",
        "identifier",
        "=",
        "if",
        "then",
        "end",
        "while",
        "loop",
        "input",
        "output",
        "(",
        ")",
    };

    if (accept(token))
        return true;
    error(fmt::format("error: expected '{}'\n", tokenNames[token - 20]));
    return false;
}

void Parser::error(const std::string &message)
{
    std::cerr << lexer->getLine() << message;
    exit(-1);
}

bool Parser::idExists(const std::string &id)
{
    return std::find(idTable.begin(), idTable.end(), id) != idTable.end();
}

void Parser::run()
{
    std::cout << "PROGRAM\n";

    expect(PROGRAM);
    while (!accept(BEGIN))
        declSec();
    stmtSec();
}

void Parser::declSec()
{
    std::cout << "DECL_SEC\n";
    decl();
}

void Parser::decl()
{
    std::cout << "DECL\n";

    idList(true);
    expect(COLON);
    if (!accept(INT_TYPE) && !accept(FLOAT_TYPE) && !accept(DOUBLE_TYPE))
        error("error: invalid declaration type\n");
    expect(SEMIC);
}

void Parser::idList(bool isDeclaring)
{
    std::cout << "ID_LIST\n";

    if (isDeclaring)
        idTable.push_back(lexer->getLexeme());
    else if (!idExists(lexer->getLexeme()))
        error("error: undeclared identifier\n");

    expect(IDENT);
    if (accept(COMMA))
        idList(isDeclaring);
}

void Parser::stmtSec()
{
    std::cout << "STMT_SEC\n";

    stmt();
    if (nextToken != END && nextToken != ELSE)
        stmtSec();
}

void Parser::stmt()
{
    std::cout << "STMT\n";

    switch (nextToken)
    {
    case IDENT:
        assign();
        break;
    case IF:
        ifStmt();
        break;
    case WHILE:
        whileStmt();
        break;
    case INPUT:
        input();
        break;
    case OUTPUT:
        output();
        break;
    default:
        error("error: invalid statement\n");
    }
}

void Parser::assign()
{
    std::cout << "ASSIGN\n";

    if (!idExists(lexer->getLexeme()))
        error("erorr: undeclared identifier\n");

    expect(IDENT);
    expect(COLON);
    expect(EQUAL_OP);
    expr();
    expect(SEMIC);
}

void Parser::ifStmt()
{
    std::cout << "IF_STMT\n";

    expect(IF);
    comp();
    expect(THEN);
    stmtSec();
    if (accept(ELSE))
        stmtSec();
    expect(END);
    expect(IF);
    expect(SEMIC);
}

void Parser::whileStmt()
{
    std::cout << "WHILE_STMT\n";

    expect(WHILE);
    comp();
    expect(LOOP);
    stmtSec();
    expect(END);
    expect(LOOP);
    expect(SEMIC);
}

void Parser::input()
{
    std::cout << "INPUT\n";

    expect(INPUT);
    idList();
    expect(SEMIC);
}

void Parser::output()
{
    std::cout << "OUTPUT\n";

    expect(OUTPUT);
    if (nextToken == IDENT)
        idList();
    else if (!accept(NUM))
        error("error: unexpected token\n");
    expect(SEMIC);
}

void Parser::expr()
{
    std::cout << "EXPR\n";

    factor();
    if (accept(ADD_OP) || accept(SUB_OP))
        expr();
}

void Parser::factor()
{
    std::cout << "FACTOR\n";

    operand();
    if (accept(MULT_OP) || accept(DIV_OP))
        factor();
}

void Parser::operand()
{
    std::cout << "OPERAND\n";

    if (accept(LEFT_PAREN))
    {
        expr();
        expect(RIGHT_PAREN);
    }
    else if (nextToken == IDENT)
    {
        if (!idExists(lexer->getLexeme()))
            error("error: undeclared identifier\n");
        expect(IDENT);
    }
    else if (!accept(NUM))
        error("error: invalid syntax\n");
}

void Parser::comp()
{
    std::cout << "COMP\n";

    expect(LEFT_PAREN);
    operand();
    if (accept(LT_OP))
        accept(GT_OP);
    else if (!accept(EQUAL_OP) && !accept(GT_OP))
        error("error: invalid comparison operator\n");
    operand();
    expect(RIGHT_PAREN);
}