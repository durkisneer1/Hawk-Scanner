#include <iostream>

#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return EXIT_FAILURE;
    }

    const char *filePath = argv[1];
    Lexer lexer(filePath);
    Parser parser(&lexer);
    parser.run();

    return EXIT_SUCCESS;
}
