//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_JMPINSTRUCTION_H
#define XLANG_JMPINSTRUCTION_H

#include "Instruction.h"
#include "../Target.h"

#include <memory>

namespace xlang {
    namespace compiler {
        namespace instructions {
            class JmpInstruction : public Instruction {
            private:
                std::unique_ptr<Target> target;
            public:
                explicit JmpInstruction(std::unique_ptr<Target> _target) : target(std::move(_target)) {}

                Target *getTarget() const {
                    return target.get();
                }
            };
        }
    }
}

#endif //XLANG_JMPINSTRUCTION_H
