#include <iostream>
#include "parser/CodeFile.h"
#include "parser/Parser.h"
#include "parser/interpreter/Assembler.h"

int main() {

    Parser parser(L"/Users/nils.van.eijk/Desktop/test/", L"main.x");
    parser.Parse();

    Assembler assembler(parser);
    assembler.Assemble();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}