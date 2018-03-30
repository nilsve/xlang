//
// Created by Nils van Eijk on 30-03-18.
//

#ifndef XLANG_NASMASSEMBLER_H
#define XLANG_NASMASSEMBLER_H

#include "AssemblerBase.h"
#include "../../interpreter/Function.h"
#include "../../interpreter/Module.h"

class NasmAssembler : public AssemblerBase {
public:
    std::wstring assembleInstruction(const Instruction &instruction) const override;
    std::wstring assembleFunctionEnd() const override;
};


#endif //XLANG_NASMASSEMBLER_H
