#include <iostream>
#include "parser/interpreter/CodeFile.h"
#include "parser/interpreter/Parser.h"
#include "parser/compiler/assemblers/NasmX86Assembler.h"
#include "parser/compiler/Compiler.h"

using namespace xlang;
using namespace xlang::interpreter;
using namespace xlang::compiler;
using namespace xlang::compiler::assemblers;

int main() {
    Parser parser(L"/Users/nils.van.eijk/Desktop/test/", L"main.x");
    parser.Parse();

    Compiler<NasmX86Assembler> compiler(parser);
    compiler.setDataStorageMode(DataStorageMode::SCOPE);
    std::wcout << compiler.Compile();

    return 0;
}