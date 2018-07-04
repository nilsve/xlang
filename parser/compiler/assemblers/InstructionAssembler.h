//
// Created by Nils van Eijk on 02-07-18.
//

#ifndef XLANG_INSTRUCTIONASSEMBLER_H
#define XLANG_INSTRUCTIONASSEMBLER_H

#include <string>

namespace xlang::compiler {
    namespace instructions {
        class Instruction;
    }

    namespace assemblers {

        class AssemblerBase;

        template <typename T>
        class InstructionAssembler : public utils::non_copyable {
        protected:
            const AssemblerBase* assemblerBase;
        public:
            InstructionAssembler() = delete;
            explicit InstructionAssembler(const AssemblerBase& _assemblerBase) : assemblerBase(&_assemblerBase) {};
            virtual std::wstring Assemble(const T& instruction) = 0;
            static inline bool isType(const compiler::instructions::Instruction* instruction) {
                return dynamic_cast<const T*>(instruction) != nullptr;
            }
        };
    }
}


#endif //XLANG_INSTRUCTIONASSEMBLER_H
