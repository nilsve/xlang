#include "parser/interpreter/CodeFile.h"
#include "parser/interpreter/Parser.h"
#include "parser/compiler/assemblers/x86/NasmX86Assembler.h"
#include "parser/compiler/Compiler.h"

#include <iostream>
#include <fstream>
#include <gtkmm-3.0/gtkmm.h>

using namespace xlang;
using namespace xlang::interpreter;
using namespace xlang::compiler;
using namespace xlang::compiler::assemblers;

using namespace std;

int main(int argc, char *argv[]) {

    /*auto app =
            Gtk::Application::create(argc, argv,
                                     "org.gtkmm.examples.base");

    Gtk::Window window;
    window.set_default_size(200, 200);

    Gtk::Button button("few", true);
    window.add(button);

    return app->run(window);*/

    srand(0); // Predictable scope names etc

    Parser parser(L"/Users/nils.van.eijk/Desktop/test/", L"main.x");
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