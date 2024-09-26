#pragma once

#include <string>

class Lexer;

class Parser
{
public:
    explicit Parser(Lexer *lexer);
    ~Parser() = default;

    void run();

private:
    Lexer *lexer;
    int nextToken;

    bool accept(int token);
    bool expect(int token);
    void error(const std::string &message);

    void declSec();
    void decl();
    void idList();
    void stmtSec();
    void stmt();
    void assign();
    void ifStmt();
    void whileStmt();
    void input();
    void output();
    void expr();
    void factor();
    void operand();
    void comp();
};
