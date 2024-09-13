#include <ctype.h>
#include <iostream>
#include <unordered_map>
#include <string>

// Variables
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

// Functions
void addChar();
void getChar();
void skipWhitespace();
int lex();

// Character classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int main()
{
    if ((in_fp = fopen("../front.in", "r")) == nullptr)
    {
        std::cout << "ERROR - Cannot open front.in" << std::endl;
        return EXIT_FAILURE;
    }

    getChar();
    do
    {
        lex();
    } while (nextToken != EOF);

    return EXIT_SUCCESS;
}

int lookUp(char ch)
{
    static const std::unordered_map<char, int> tokenMap = {
        {'(', LEFT_PAREN},
        {')', RIGHT_PAREN},
        {'+', ADD_OP},
        {'-', SUB_OP},
        {'*', MULT_OP},
        {'/', DIV_OP},
    };

    addChar();

    auto it = tokenMap.find(ch);
    nextToken = (it != tokenMap.end()) ? it->second : EOF;

    return nextToken;
}

void addChar()
{
    if (lexLen >= 99)
        std::cout << "ERROR - Lexeme is too long" << std::endl;

    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
}

void getChar()
{
    if ((nextChar = getc(in_fp)) == EOF)
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

void skipWhitespace()
{
    while (isspace(nextChar))
        getChar();
}

int lex()
{
    lexLen = 0;
    skipWhitespace();
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
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }

    std::cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << std::endl;
    return nextToken;
}