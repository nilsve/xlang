//
// Created by Nils van Eijk on 30-03-18.
//

#ifndef XLANG_NasmX86Assembler_H
#define XLANG_NasmX86Assembler_H

#include "AssemblerBase.h"
#include "../../interpreter/Function.h"
#include "../../interpreter/Module.h"

class NasmX86Assembler : public AssemblerBase {
public:
    std::wstring assembleInstruction(const Instruction &instruction) const override;

    std::wstring assembleFunctionStart(const Function &function) const override;
    std::wstring assembleFunctionEnd() const override;

    std::wstring assembleScopeStart(const Scope &scope) const override;
    std::wstring assembleScopeEnd(const Scope& scope) const override;

};


#endif //XLANG_NasmX86Assembler_H
