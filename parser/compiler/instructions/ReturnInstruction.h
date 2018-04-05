//
// Created by Nils van Eijk on 05-04-18.
//

#ifndef XLANG_RETURNINSTRUCTION_H
#define XLANG_RETURNINSTRUCTION_H

#include "Instruction.h"

namespace xlang {
    namespace compiler {
        namespace instructions {

            class Scope;

            class Variable;

            class ReturnInstruction : public Instruction {
            private:
                const Scope *scope;
                const Variable *returnVariable;
            public:
                explicit ReturnInstruction(const Scope *_scope, const Variable *_returnVariable) : scope(_scope),
                                                                                                   returnVariable(
                                                                                                           _returnVariable) {}

                const Scope *getScope() const {
                    return scope;
                }

                const Variable *getReturnVariable() const {
                    return returnVariable;
                }
            };
        }
    }
}

#endif //XLANG_RETURNINSTRUCTION_H
