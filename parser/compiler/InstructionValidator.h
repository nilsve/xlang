//
// Created by Nils van Eijk on 31-03-18.
//

#ifndef XLANG_INSTRUCTIONVALIDATOR_H
#define XLANG_INSTRUCTIONVALIDATOR_H

#include "instructions/Instruction.h"
#include "instructions/CallInstruction.h"
#include "../Parser.h"

#include <iostream>

class Target;

class InstructionValidator {
    private:
        const Parser& parser;

        bool findScopeId(const Scope& rootScope, std::wstring scopeId) const;

        void handleTarget(const Instruction &instruction, Target& target) const;

    public:
        explicit InstructionValidator(const Parser& _parser) : parser(_parser) {}

        void validateAndPatchInstruction(Instruction& instruction) const;
};

#endif //XLANG_INSTRUCTIONVALIDATOR_H
