//
// Created by Nils van Eijk on 30-03-18.
//

#ifndef XLANG_NasmX86Assembler_H
#define XLANG_NasmX86Assembler_H

#include "AssemblerBase.h"
#include "../../interpreter/Function.h"
#include "../../interpreter/Module.h"
#include "../instructions/AssignInstruction.h"

namespace xlang {
    namespace compiler {
        namespace assemblers {

            class NasmX86Assembler : public AssemblerBase {
            private:
                std::wstring assembleAssignInstruction(const xlang::compiler::instructions::AssignInstruction &instruction) const;

            public:
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
