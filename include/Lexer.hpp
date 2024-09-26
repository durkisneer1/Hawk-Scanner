#pragma once

#include <string>
#include <fstream>

class Lexer
{
public:
    explicit Lexer(const std::string &fileName);
    ~Lexer();

    void lookUp(char ch);
    void addChar();
    void getChar();
    int lex();
    std::string getLexeme();
    std::string getLine();

private:
    int charClass;
    std::string lexeme;
    char nextChar;
    int nextToken;
    std::ifstream readFile;
    int currentLine = 1;
    int currentColumn = 1;
    std::string fileName;
};
