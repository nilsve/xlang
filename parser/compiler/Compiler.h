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
class Compiler : public Assembler, public non_copyable {
    static_assert(std::is_base_of<AssemblerBase, Assembler>::value);

private:
    const Parser& parser;

    std::wstring output;

    const Module* findModule(const std::vector<std::unique_ptr<Module>>& modules, std::wstring moduleName) const {
        for (auto& module : modules) {
            if (module->getModuleName() == moduleName) {
                return module.get();
            }
        }

        return nullptr;
    }
    const Function* findFunction(const Module& module, std::wstring functionName) const {
        for (auto& function : module.getFunctions()) {
            if (function->getFunctionName() == functionName) {
                return function.get();
            }
        }

        return nullptr;
    }

    void compileModules(const std::vector<std::unique_ptr<Module>> &modules) {
        for (auto& module : modules) {
            compileModule(*module);
        }
    }
    void compileModule(const Module &module) {
        appendOutput(L"");

        for (auto& function : module.getFunctions()) {
            compileFunction(*function);
        }
    }
    void compileFunction(const Function &function) {
        compileScope(*function.getRootScope());
    }

    void throwError(std::wstring message) const {
        return throwError(Utils::wstring_to_utf8(message));
    }
    void throwError(std::string message) const {
        throw std::invalid_argument(message.c_str());
    }

    void compileScope(const Scope &scope) {
        auto& instructions = scope.getInstructions();

        for (auto& instruction : instructions) {
            assembleInstruction(instruction);
        }
    }

    void assembleInstruction(const std::unique_ptr<Instruction> &instruction);
    void appendOutput(std::wstring line) {
        output += line;
    }

public:
    explicit Compiler(const Parser& _parser) : parser(_parser){
        output.reserve(2048);
    }

    void Compile() {
        const auto& modules = parser.getModules();

        compileModules(modules);

        if (auto mainModule = findModule(modules, L"main")) {
            if (auto mainFunction = findFunction(*mainModule, L"main")) {

            }
        }
    }
};


#endif //XLANG_ASSEMBLER_H
