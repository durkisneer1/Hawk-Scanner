#pragma once

#include <string>
#include <vector>

class Lexer;

class Parser
{
public:
    explicit Parser(Lexer *lexer);
    ~Parser();

    void run();

private:
    Lexer *lexer;
    int nextToken;
    std::vector<std::string> idTable;

    bool accept(int token);
    bool expect(int token);
    void error(const std::string &message);

    void declSec();
    void decl();
    void idList(bool isDeclaring = false);
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
