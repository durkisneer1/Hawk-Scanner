#include <iostream>
#include <unordered_map>
#include <fmt/format.h>

#include "Lexer.hpp"
#include "Constants.hpp"

Lexer::Lexer(const std::string &fileName)
{
    readFile.open(fileName);
    if (!readFile.is_open())
        throw std::runtime_error("ERROR - Cannot open " + fileName);
    this->fileName = fileName;
    getChar();
}

Lexer::~Lexer()
{
    readFile.close();
}

void Lexer::lookUp(char ch)
{
    static const std::unordered_map<char, int> tokenMap = {
        {'=', EQUAL_OP},
        {'+', ADD_OP},
        {'-', SUB_OP},
        {'*', MULT_OP},
        {'/', DIV_OP},
        {'(', LEFT_PAREN},
        {')', RIGHT_PAREN},
        {':', COLON},
        {';', SEMIC},
        {',', COMMA},
        {'<', LT_OP},
        {'>', GT_OP},
    };

    addChar();
    nextToken = (tokenMap.find(ch) != tokenMap.end()) ? tokenMap.at(ch) : UNKNOWN;
}

void Lexer::addChar()
{
    lexeme.push_back(nextChar);
}

void Lexer::getChar()
{
    if (!readFile.get(nextChar))
    {
        charClass = EOF;
        return;
    }

    if (isalpha(nextChar))
        charClass = LETTER;
    else if (isdigit(nextChar) || nextChar == '.')
        charClass = DIGIT;
    else
        charClass = UNKNOWN;
}

int Lexer::lex()
{
    static const std::unordered_map<std::string, int> reservedWords = {
        {"program", PROGRAM},
        {"begin", BEGIN},
        {"end", END},
        {"if", IF},
        {"while", WHILE},
        {"input", INPUT},
        {"output", OUTPUT},
        {"then", THEN},
        {"else", ELSE},
        {"loop", LOOP},
        {"int", INT_TYPE},
        {"float", FLOAT_TYPE},
        {"double", DOUBLE_TYPE},
    };

    lexeme.clear();
    while (isspace(nextChar))
    {
        if (nextChar == '\n')
        {
            currentRow++;
            currentColumn = 0;
        }
        currentColumn++;
        getChar();
    }

    switch (charClass)
    {
    case LETTER:
        do
        {
            currentColumn++;
            addChar();
            getChar();
        } while (charClass == LETTER || charClass == DIGIT);
        nextToken = (reservedWords.find(lexeme) != reservedWords.end()) ? reservedWords.at(lexeme) : IDENT;
        break;
    case DIGIT:
        do
        {
            currentColumn++;
            addChar();
            getChar();
        } while (charClass == DIGIT);
        nextToken = NUM;
        break;
    case UNKNOWN:
        currentColumn++;
        lookUp(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme = "EOF";
        break;
    }

    return nextToken;
}

std::string Lexer::getLine()
{
    return fmt::format("{}:{}:{}", fileName, currentRow, currentColumn);
}