#include <iostream>
#include <unordered_map>

#include "Lexical.hpp"
#include "Constants.hpp"

LexicalAnalyzer::LexicalAnalyzer(const std::string &fileName)
{
    readFile.open(fileName);
    if (!readFile.is_open())
        throw std::runtime_error("ERROR - Cannot open " + fileName);
    getChar();
}

LexicalAnalyzer::~LexicalAnalyzer()
{
    readFile.close();
}

void LexicalAnalyzer::lookUp(char ch)
{
    static const std::unordered_map<char, int> tokenMap = {
        {'=', ASSIGN_OP},
        {'+', ADD_OP},
        {'-', SUB_OP},
        {'*', MULT_OP},
        {'/', DIV_OP},
        {'(', LEFT_PAREN},
        {')', RIGHT_PAREN},
    };

    addChar();
    nextToken = (tokenMap.find(ch) != tokenMap.end()) ? tokenMap.at(ch) : UNKNOWN;
}

void LexicalAnalyzer::addChar()
{
    lexeme.push_back(nextChar);
}

void LexicalAnalyzer::getChar()
{
    if (!readFile.get(nextChar))
    {
        charClass = EOF;
        return;
    }

    if (isalpha(nextChar))
        charClass = LETTER;
    else if (isdigit(nextChar))
        charClass = DIGIT;
    else
        charClass = UNKNOWN;
}

int LexicalAnalyzer::lex()
{
    lexeme.clear();
    while (isspace(nextChar))
        getChar();

    switch (charClass)
    {
    case LETTER:
        do
        {
            addChar();
            getChar();
        } while (charClass == LETTER || charClass == DIGIT);
        nextToken = IDENT;
        break;
    case DIGIT:
        do
        {
            addChar();
            getChar();
        } while (charClass == DIGIT);
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookUp(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme = "EOF";
        break;
    }

    std::cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << std::endl;
    return nextToken;
}
