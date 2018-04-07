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

using namespace std;

int main() {

    srand(0); // Predictable scope names etc

    Parser parser(L"/Users/nilsvaneijk/Desktop/test/", L"main.x");
    parser.Parse();

    Compiler<NasmX86Assembler> compiler(parser);
    compiler.setDataStorageMode(DataStorageMode::SCOPE);
    
    auto translated = compiler.Compile();
    wcout << translated;

    wofstream out("/Users/nilsvaneijk/Desktop/test/output.asm");
    out << L"section .text" << endl << L"global start" << endl << L"start:" << endl << endl;
    out.write(translated.c_str(), translated.size());
    out.close();


    return 0;
}