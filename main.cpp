#include <iostream>
#include "parser/CodeFile.h"
#include "parser/Parser.h"

int main() {

    Parser parser(L"/Users/nilsvaneijk/Desktop/test/", L"main.x");
    parser.Parse();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}