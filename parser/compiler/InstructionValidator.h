//
// Created by Nils van Eijk on 31-03-18.
//

#ifndef XLANG_INSTRUCTIONVALIDATOR_H
#define XLANG_INSTRUCTIONVALIDATOR_H

#include "instructions/Instruction.h"
#include "instructions/CallInstruction.h"
#include "../Parser.h"

#include <iostream>

class InstructionValidator {
    private:
        const Parser& parser;

        bool findScopeId(const Scope& rootScope, std::wstring scopeId) const;

        void validateCallInstruction(const CallInstruction& callInstruction) const;

    public:
        InstructionValidator(const Parser& _parser) : parser(_parser) {}

        void validateInstruction(const Instruction& instruction) const;
};

#endif //XLANG_INSTRUCTIONVALIDATOR_H
