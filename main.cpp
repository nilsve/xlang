#include "parser/interpreter/CodeFile.h"
#include "parser/interpreter/Parser.h"
#include "parser/compiler/assemblers/NasmX86Assembler.h"
#include "parser/compiler/Compiler.h"

#include <iostream>
#include <fstream>

using namespace xlang;
using namespace xlang::interpreter;
using namespace xlang::compiler;
using namespace xlang::compiler::assemblers;

int main() {
    Parser parser(L"/Users/nilsvaneijk/Desktop/test/", L"main.x");
    parser.Parse();

    Compiler<NasmX86Assembler> compiler(parser);
    compiler.setDataStorageMode(DataStorageMode::SCOPE);
    
    auto translated = compiler.Compile();
    std::wcout << translated;

    std::wofstream out("/Users/nilsvaneijk/Desktop/test/output.asm");
    out.write(translated.c_str(), translated.size());
    out.close();


    return 0;
}