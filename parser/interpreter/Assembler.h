//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_ASSEMBLER_H
#define XLANG_ASSEMBLER_H


#include "../../utils/non_copyable.h"
#include "../Parser.h"

#include <vector>
#include <map>

class Assembler : public non_copyable {
private:
    const Parser& parser;

    std::vector<unsigned char> output;
    unsigned long currentOutputOffset = 0;

    size_t appendOutput(std::vector<unsigned char> instructions);

    const Module* findModule(const std::vector<std::unique_ptr<Module>>& modules, std::wstring moduleName) const;
    const Function* findFunction(const Module& module, std::wstring functionName) const;

    std::map<std::wstring, unsigned long> functionMap; // string = modulename.functionname, unsigned long = relative address

    void assembleModules(const std::vector<std::unique_ptr<Module>>& modules);
    void assembleModule(const Module& module);
    void assembleFunction(const Function& function);
public:
    explicit Assembler(const Parser& _parser);
    void Assemble();

    void throwError(std::wstring message) const;
    void throwError(std::string message) const;

    void assembleScope(const Scope &scope);
};


#endif //XLANG_ASSEMBLER_H
