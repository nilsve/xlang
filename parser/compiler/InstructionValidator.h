//
// Created by Nils van Eijk on 31-03-18.
//

#ifndef XLANG_INSTRUCTIONVALIDATOR_H
#define XLANG_INSTRUCTIONVALIDATOR_H

#include "instructions/Instruction.h"
#include "instructions/CallInstruction.h"
#include "../interpreter/Parser.h"

#include <iostream>

namespace xlang {
    namespace compiler {

        class Target;

        class InstructionValidator {
        private:
            const interpreter::Parser &parser;

            bool findScopeId(const interpreter::Scope &rootScope, std::wstring scopeId) const;

            void handleTarget(const compiler::instructions::Instruction &instruction, compiler::Target &target) const;

        public:
            explicit InstructionValidator(const interpreter::Parser &_parser) : parser(_parser) {}

            void validateAndPatchInstruction(compiler::instructions::Instruction &instruction) const;
        };
    }
}

#endif //XLANG_INSTRUCTIONVALIDATOR_H
