//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_ASSEMBLER_H
#define XLANG_ASSEMBLER_H

#include "../../utils/non_copyable.h"
#include "../Parser.h"
#include "../../utils/Utils.h"
#include "./assemblers/AssemblerBase.h"
#include "InstructionValidator.h"
#include "instructions/JmpInstruction.h"
#include "StrongTarget.h"

#include <vector>
#include <type_traits>
#include <map>
#include <iostream>

template <typename Assembler>
class Compiler : public non_copyable {
    static_assert(std::is_base_of<AssemblerBase, Assembler>::value, "Assembler has to be derrived from AssemblerBase");
private:
    const Parser& parser;
    const std::unique_ptr<InstructionValidator> validator;
    Assembler assembler;
    DataStorageMode dataStorageMode = DataStorageMode::section;

    std::vector<std::wstring> code;
    std::vector<std::wstring> data;

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
            for (auto& function : module->getFunctions()) {

                StrongTarget target(*function->getRootScope());
                JmpInstruction jmp(std::unique_ptr<Target>((Target*)(new StrongTarget(*function->getRootScope()))));
                appendCodeBlock(assembler.assembleFunctionStart(*function) + L"\n" + assembler.assembleInstruction(jmp));

                compileScope(*function->getRootScope());

                appendCodeBlock(assembler.assembleFunctionEnd());
            }
        }
    }

    void compileScope(const Scope &scope) {

        std::wstring scopeCode;
        scopeCode += assembler.assembleScopeStart(scope) + L"\n";

        for (auto& instruction : scope.getInstructions()) {
            validator->validateInstruction(*instruction);
            scopeCode += assembler.assembleInstruction(*instruction) + L"\n";
        }

        scopeCode += assembler.assembleScopeEnd(scope);

        appendCodeBlock(scopeCode);

        auto& childScopes = scope.getScopes();

        for (auto& childScope : childScopes) {
            compileScope(*childScope);
        }
    }

    void compileData(const Data& data) {
        auto result = assembler->compileData(data);

        switch (dataStorageMode) {
            case DataStorageMode::section:

                break;
            case DataStorageMode::scope:
                break;
            default:
                assert(false);
        }
    }

    void appendDataBlock(std::wstring _data) {
        data.push_back(std::move(_data));
    }

    void appendCodeBlock(std::wstring _code) {
        code.push_back(std::move(_code));
    }

public:
    explicit Compiler(const Parser& _parser) : parser(_parser), validator(std::make_unique<InstructionValidator>(parser)) {
        code.reserve(2048);
    }

    std::wstring Compile() {
        const auto& modules = parser.getModules();

        compileModules(modules);

        if (auto mainModule = findModule(modules, L"main")) {
            if (auto mainFunction = findFunction(*mainModule, L"main")) {

            }
        }

        std::wstring result;
        unsigned long size = 0;
        for (std::wstring& block : code) {
            size += block.size();
        }

        result.reserve(size);
        for (std::wstring& block : code) {
            result += block + L"\n";
        }

        return result;
    }

    void setDataStorageMode(DataStorageMode dataStorageMode) {
        Compiler::dataStorageMode = dataStorageMode;
    }
};


#endif //XLANG_ASSEMBLER_H
