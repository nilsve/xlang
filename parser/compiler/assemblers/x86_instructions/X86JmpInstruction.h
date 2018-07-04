//
// Created by Nils van Eijk on 04-07-18.
//

#ifndef XLANG_X86JMPINSTRUCTION_H
#define XLANG_X86JMPINSTRUCTION_H

#include "../../instructions/JmpInstruction.h"
#include "../InstructionAssembler.h"
#include "../NasmX86Assembler.h"

#include <string>

namespace xlang::compiler::assemblers::x86_instructions {
    class X86JmpInstruction: public InstructionAssembler<instructions::JmpInstruction> {
    public:
        X86JmpInstruction(const AssemblerBase &base) : InstructionAssembler(base) {}

        std::wstring Assemble(const instructions::JmpInstruction &instruction) {
            return L"jmp " + instruction.getTarget()->getFullPath();
        }
    };
}


#endif //XLANG_X86JMPINSTRUCTION_H
