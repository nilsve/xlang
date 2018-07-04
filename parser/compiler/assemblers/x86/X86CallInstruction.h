//
// Created by Nils van Eijk on 04-07-18.
//

#ifndef XLANG_X86CALLINSTRUCTION_H
#define XLANG_X86CALLINSTRUCTION_H

#include "../../instructions/CallInstruction.h"
#include "../InstructionAssembler.h"
#include "NasmX86Assembler.h"

#include <string>

namespace xlang::compiler::assemblers::x86 {
    class X86CallInstruction: public InstructionAssembler<instructions::CallInstruction> {
    public:
        X86CallInstruction(const AssemblerBase &base) : InstructionAssembler(base) {}

        std::wstring Assemble(const instructions::CallInstruction &instruction) {
            std::wstring result;

            auto& parameters = instruction.getParameters();
            if (!parameters.empty()) {
                for (auto i = static_cast<long>(parameters.size()) - 1; i >= 0; i--) {
                    auto& parameter = parameters[i];
                    result += L"push DWORD [ebp - " + std::to_wstring(assemblerBase->getVariableIndex(parameter.variable.getVariableIndex()) * assemblerBase->getRegisterSize()) + L"]\n";
                }
            }
            return result + L"call " + instruction.getTarget()->getFullPath();
        }
    };
}


#endif //XLANG_X86CALLINSTRUCTION_H
