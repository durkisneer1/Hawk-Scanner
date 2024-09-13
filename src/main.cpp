#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

// Variables
int charClass;
std::string lexeme;
char nextChar;
int nextToken;
std::ifstream readFile;

// Functions
void addChar();
void getChar();
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
    readFile.open("../front.in");
    if (!readFile.is_open())
    {
        std::cerr << "ERROR - Cannot open front.in" << std::endl;
        return EXIT_FAILURE;
    }

    getChar();
    do
    {
        lex();
    } while (nextToken != EOF);

    readFile.close();
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
    lexeme.push_back(nextChar);
}

void getChar()
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

int lex()
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
