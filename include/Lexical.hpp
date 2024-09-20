#pragma once

#include <string>
#include <fstream>

class LexicalAnalyzer
{
public:
    explicit LexicalAnalyzer(const std::string &fileName);
    ~LexicalAnalyzer();

    void lookUp(char ch);
    void addChar();
    void getChar();
    int lex();

private:
    int charClass;
    std::string lexeme;
    char nextChar;
    int nextToken;
    std::ifstream readFile;
};
