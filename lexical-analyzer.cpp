#include <iostream>
#include <fstream>
#include <string>

// Lexer that returns a list of tokens and lexemes from a given string
void lexer(std::string sourceCode)
{
    // Test output
    std::cout << sourceCode;
}

int main()
{
    // Represents the source code from a given input file
    std::string sourceCode;

    // Input source code file that will pass through the lexer
    std::ifstream inputFile;

    inputFile.open("input_scode.txt");

    // Extracts characters from input file and stores it in a string
    getline(inputFile, sourceCode);

    lexer(sourceCode);

    return 0;
}