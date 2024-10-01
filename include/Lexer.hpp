#pragma once

#include <string>
#include <fstream>

struct Position
{
    int line = 1;
    int column = 1;
};

class Lexer
{
public:
    explicit Lexer(const std::string &fileName);
    ~Lexer();

    void lookUp(char ch);
    void addChar();
    void getChar();
    void passed();
    int lex();
    std::string getLexeme();
    std::string getLine();

private:
    int charClass;
    int lastCharClass;
    bool pointExists = false; // Making sure real nums only have one point
    int digitCount = 0;
    std::string lexeme;
    char nextChar;
    int nextToken;
    std::ifstream readFile;
    std::string fileName;
    Position currentPosition;
    Position lastPosition;
};
