#include "Lexer.hpp"
#include "Parser.hpp"

int main()
{
    Lexer lexer("../test/moderate.hawk");
    Parser parser(&lexer);
    parser.run();

    return EXIT_SUCCESS;
}
