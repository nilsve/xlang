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

    std::weak_ptr<Module> findModule(std::vector<std::shared_ptr<Module>>& modules, std::wstring moduleName);
    std::weak_ptr<Function> findFunction(const Module& module, std::wstring functionName);

    std::map<std::wstring, unsigned long> functionMap; // string = modulename.functionname, unsigned long = relative address

    void assembleModules(std::vector<std::shared_ptr<Module>>& modules);
    void assembleModule(const Module& module);
    void assembleFunction(const Function& function);
public:
    Assembler(const Parser& _parser);
    void Assemble();

    void throwError(std::wstring message) const;
    void throwError(std::string message) const;

    void assembleScope(const Scope &scope);
};


#endif //XLANG_ASSEMBLER_H
