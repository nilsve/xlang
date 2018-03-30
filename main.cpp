#include <iostream>
#include "parser/CodeFile.h"
#include "parser/Parser.h"
#include "parser/compiler/assemblers/NasmAssembler.h"
#include "parser/compiler/Compiler.h"
#include <ctime>

int main() {

    clock_t start = clock();

    for(int i = 0; i < 10000; i++) {
        Parser parser(L"/Users/nils.van.eijk/Desktop/test/", L"main.x");
        parser.Parse();

        Compiler<NasmAssembler> compiler(parser);
//        compiler.Compile();
    }

    clock_t stop = clock();

    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);

    return 0;
}