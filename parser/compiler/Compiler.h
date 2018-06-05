//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_ASSEMBLER_H
#define XLANG_ASSEMBLER_H

#include "../../utils/non_copyable.h"
#include "../interpreter/Parser.h"
#include "../../utils/Utils.h"
#include "./assemblers/AssemblerBase.h"
#include "InstructionValidator.h"
#include "instructions/JmpInstruction.h"
#include "StrongTarget.h"

#include <vector>
#include <cassert>
#include <type_traits>
#include <map>
#include <iostream>

namespace xlang {
    namespace compiler {

        template<typename Assembler>
        class Compiler : public utils::non_copyable {
            static_assert(std::is_base_of<assemblers::AssemblerBase, Assembler>::value,
                          "Assembler has to be derived from AssemblerBase");
        private:
            const interpreter::Parser &parser;
            const std::unique_ptr<InstructionValidator> validator;
            Assembler assembler;
            interpreter::DataStorageMode dataStorageMode = interpreter::DataStorageMode::SECTION;

            std::vector<std::wstring> code;
            std::vector<std::wstring> data;

            const interpreter::Module *
            findModule(const std::vector<std::unique_ptr<interpreter::Module>> &modules, const std::wstring &moduleName) const {
                for (auto &module : modules) {
                    if (module->getId() == moduleName) {
                        return module.get();
                    }
                }

                return nullptr;
            }

            const interpreter::Function *findFunction(const interpreter::Module &module, const std::wstring &functionName) const {
                for (auto &function : module.getFunctions()) {
                    if (function->getId() == functionName) {
                        return function.get();
                    }
                }

                return nullptr;
            }

            void compileModules(const std::vector<std::unique_ptr<interpreter::Module>> &modules) {
                for (auto &module : modules) {
                    for (auto &function : module->getFunctions()) {

                        auto target = std::unique_ptr<Target>((Target *) (new StrongTarget(*function->getRootScope())));
                        instructions::JmpInstruction jmp(std::move(target));
                        appendCodeBlock(
                                assembler.assembleFunctionStart(*function) + L"\n" +
                                assembler.assembleInstruction(jmp));

                        compileScope(*function->getRootScope());

                        appendCodeBlock(assembler.assembleFunctionEnd(*function));
                    }
                }
            }

            void compileScope(const interpreter::Scope &scope) {

                for (auto &data : scope.getData()) {
                    // Numbers get inlined
                    if (!data->getIsNumber()) {
                        compileData(*data);
                    }
                }

                std::wstring scopeCode;
                scopeCode += assembler.assembleScopeStart(scope) + L"\n";

                if (scope.getIsRawBlock()) {
                    scopeCode += scope.getRawCode();
                } else {
                    for (auto &instruction : scope.getInstructions()) {
                        validator->validateAndPatchInstruction(*instruction);
                        scopeCode += assembler.assembleInstruction(*instruction) + L"\n";
                    }
                }

                scopeCode += assembler.assembleScopeEnd(scope);

                appendCodeBlock(scopeCode);

                auto &childScopes = scope.getScopes();

                for (auto &childScope : childScopes) {
                    compileScope(*childScope);
                }
            }

            void compileData(const interpreter::Data &data) {
                auto result = assembler.assembleData(data);

                switch (dataStorageMode) {
                    case interpreter::DataStorageMode::SECTION:
                        appendDataBlock(std::move(result));
                        break;
                    case interpreter::DataStorageMode::SCOPE:
                        appendCodeBlock(std::move(result));
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
            explicit Compiler(const interpreter::Parser &_parser) : parser(_parser),
                                                       validator(std::make_unique<InstructionValidator>(parser)) {
//        code.reserve(2048);
            }

            std::wstring Compile() {
                const auto &modules = parser.getModules();

                compileModules(modules);

                std::wstring result;

                if (auto mainModule = findModule(modules, L"main")) {
                    if (auto mainFunction = findFunction(*mainModule, L"main")) {
                        auto target = std::unique_ptr<Target>((Target*)new StrongTarget(*mainFunction));
                        instructions::JmpInstruction jmp(std::move(target));
                        result += assembler.assembleInstruction(jmp) + L"\n";
                    } else {
                        utils::Utils::throwError("Function `main` in module `main` not found!");
                    }
                } else {
                    utils::Utils::throwError("Module `main` not found!");
                }

                unsigned long size = 0;
                for (std::wstring &block : code) {
                    size += block.size();
                }

                result.reserve(size);
                for (std::wstring &block : code) {
                    result += block + L"\n";
                }

                return result;
            }

            void setDataStorageMode(interpreter::DataStorageMode dataStorageMode) {
                Compiler::dataStorageMode = dataStorageMode;
            }
        };
    }
}

#endif //XLANG_ASSEMBLER_H
