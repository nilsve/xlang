//
// Created by Nils van Eijk on 02-07-18.
//

#ifndef XLANG_X86ASSIGNINSTRUCTION_H
#define XLANG_X86ASSIGNINSTRUCTION_H

#include "../../instructions/AssignInstruction.h"
#include "../InstructionAssembler.h"

#include <string>

namespace xlang::compiler::assemblers::x86 {
    class X86AssignInstruction : public InstructionAssembler<instructions::AssignInstruction> {
    public:
        X86AssignInstruction(const AssemblerBase &base) : InstructionAssembler(base) {}

        std::wstring Assemble(const instructions::AssignInstruction& instruction) {
            std::wstring result;
            if (auto target = instruction.getTarget()) {

                std::wstring source;

                if (auto data = instruction.getData()) {
                    if (data->getIsNumber()) {
                        result += L"mov DWORD [ebp - " + std::to_wstring(
                                assemblerBase->getVariableIndex(target->getVariableIndex()) *
                                assemblerBase->getRegisterSize()) + L"], " + data->getDataAsString();
                    } else {
                        result += L"mov DWORD eax, " + data->getDataId() + L"\n"
                                                                           L"mov DWORD [ebp - " + std::to_wstring(
                                assemblerBase->getVariableIndex(target->getVariableIndex()) *
                                assemblerBase->getRegisterSize()) + L"], eax";
                    }

                } else if (auto sourceVariable = instruction.getSourceVariable()) {
                    result += L"mov DWORD eax, [ebp - " + std::to_wstring(
                            assemblerBase->getVariableIndex(sourceVariable->getVariableIndex()) *
                            assemblerBase->getRegisterSize()) + L"]\n"
                                                                L"mov DWORD [ebp - " + std::to_wstring(
                            assemblerBase->getVariableIndex(target->getVariableIndex()) * assemblerBase->getRegisterSize()) +
                              L"], eax";
                } else {
                    assert(false);
                }
            } else {
                utils::Utils::throwError("Target empty for assignment instruction!");
            }

            return result;
        }
    };
}


#endif //XLANG_X86ASSIGNINSTRUCTION_H
