#include <iostream>
#include <unordered_map>
#include <fmt/format.h>

#include "Lexer.hpp"
#include "Constants.hpp"

Lexer::Lexer(const std::string &fileName)
    : fileName(fileName)
{
    readFile.open(fileName);
    if (!readFile.is_open())
        throw std::runtime_error("ERROR - Cannot open " + fileName);
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

    if (isalpha(nextChar) || nextChar == '_')
        charClass = LETTER;
    else if (isdigit(nextChar))
    {
        charClass = DIGIT;
        digitCount++;
    }
    else if (nextChar == '.' && lastCharClass == DIGIT && !pointExists)
    {
        charClass = DIGIT;
        pointExists = true;
    }
    else
        charClass = UNKNOWN;

    lastCharClass = charClass;
}

void Lexer::passed()
{
    lastPosition = currentPosition;
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
            currentPosition.line++;
            currentPosition.column = 1;
        }
        currentPosition.column++;
        getChar();
    }

    switch (charClass)
    {
    case LETTER:
        do
        {
            currentPosition.column++;
            addChar();
            getChar();
        } while (charClass == LETTER || charClass == DIGIT);

        nextToken = (reservedWords.find(lexeme) != reservedWords.end()) ? reservedWords.at(lexeme) : IDENT;
        break;
    case DIGIT:
        do
        {
            currentPosition.column++;
            addChar();
            getChar();
        } while (charClass == DIGIT);

        if (digitCount > 10)
        {
            std::cerr << getLine() << "error: too many digits";
            exit(-1);
        }

        digitCount = 0;
        nextToken = NUM;
        pointExists = false;
        break;
    case UNKNOWN:
        currentPosition.column++;
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
    return fmt::format("{}:{}:{}: ", fileName, lastPosition.line, lastPosition.column);
}

std::string Lexer::getLexeme()
{
    return lexeme;
}
