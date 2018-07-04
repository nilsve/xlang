//
// Created by Nils van Eijk on 30-03-18.
//

#ifndef XLANG_NasmX86Assembler_H
#define XLANG_NasmX86Assembler_H

#include "../AssemblerBase.h"
#include "../../../interpreter/Function.h"
#include "../../../interpreter/Module.h"

#include "X86AssignInstruction.h"
#include "X86CallInstruction.h"
#include "X86JmpInstruction.h"

#include <memory>

namespace xlang {
    namespace compiler {
        namespace assemblers {
            class NasmX86Assembler : public AssemblerBase {
            private:
                std::unique_ptr<x86::X86AssignInstruction> assignInstructionAssembler;
                std::unique_ptr<x86::X86CallInstruction> callInstructionAssembler;
                std::unique_ptr<x86::X86JmpInstruction> jmpInstructionAssembler;
            public:
                NasmX86Assembler() {
                    assignInstructionAssembler = std::make_unique<x86::X86AssignInstruction>(*this);
                    callInstructionAssembler= std::make_unique<x86::X86CallInstruction>(*this);
                    jmpInstructionAssembler= std::make_unique<x86::X86JmpInstruction>(*this);
                };

                long getRegisterSize() const override;

                int getVariableIndex(int variableIndex) const override;
                std::wstring assembleInstruction(const compiler::instructions::Instruction &instruction) const override;

                std::wstring assembleFunctionStart(const interpreter::Function &function) const override;

                std::wstring assembleFunctionEnd(const interpreter:: Function &function) const override;

                std::wstring assembleData(const interpreter::Data &data) const override;

                std::wstring assembleScopeStart(const interpreter::Scope &scope) const override;

                std::wstring assembleScopeEnd(const interpreter::Scope &scope) const override;

            };
        }
    }
}

#endif //XLANG_NasmX86Assembler_H
