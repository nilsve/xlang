#include <iostream>
#include "parser/CodeFile.h"
#include "parser/Parser.h"
#include "parser/compiler/assemblers/NasmX86Assembler.h"
#include "parser/compiler/Compiler.h"

int main() {


    Parser parser(L"/Users/nils.van.eijk/Desktop/test/", L"main.x");
    parser.Parse();

    Compiler<NasmX86Assembler> compiler(parser);
    std::wcout << compiler.Compile();

    return 0;
}