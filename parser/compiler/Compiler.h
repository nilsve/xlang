//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_ASSEMBLER_H
#define XLANG_ASSEMBLER_H

#include "../../utils/non_copyable.h"
#include "../Parser.h"
#include "../../utils/Utils.h"
#include "./assemblers/AssemblerBase.h"

#include <vector>
#include <type_traits>
#include <map>

template <typename Assembler>
class Compiler : public non_copyable {
    static_assert(std::is_base_of<AssemblerBase, Assembler>::value, "Assembler has to be derrived from AssemblerBase");
private:
    const Parser& parser;

    Assembler assembler;

    std::wstring output;

    inline const Module* findModule(const std::vector<std::unique_ptr<Module>>& modules, std::wstring moduleName) const {
        for (auto& module : modules) {
            if (module->getModuleName() == moduleName) {
                return module.get();
            }
        }

        return nullptr;
    }
    inline const Function* findFunction(const Module& module, std::wstring functionName) const {
        for (auto& function : module.getFunctions()) {
            if (function->getFunctionName() == functionName) {
                return function.get();
            }
        }

        return nullptr;
    }

    inline void compileModules(const std::vector<std::unique_ptr<Module>> &modules) {
        for (auto& module : modules) {
            for (auto& function : module->getFunctions()) {
                appendOutput(assembler.assembleFunctionStart(*function));

                compileScope(*function->getRootScope());

                appendOutput(assembler.assembleFunctionEnd());
            }
        }
    }

    inline void compileScope(const Scope &scope) {
        appendOutput(assembler.assembleScopeStart(scope));

        for (auto& instruction : scope.getInstructions()) {
            appendOutput(assembler.assembleInstruction(*instruction));
        }
    }

    void appendOutput(std::wstring line) {
        output += line + L"\n";
    }

public:
    explicit Compiler(const Parser& _parser) : parser(_parser){
        output.reserve(2048);
    }

    std::wstring Compile() {
        const auto& modules = parser.getModules();

        compileModules(modules);

        if (auto mainModule = findModule(modules, L"main")) {
            if (auto mainFunction = findFunction(*mainModule, L"main")) {

            }
        }

        return std::move(output);
    }
};


#endif //XLANG_ASSEMBLER_H
