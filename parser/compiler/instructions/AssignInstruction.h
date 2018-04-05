//
// Created by Nils van Eijk on 03-04-18.
//

#ifndef XLANG_ASSIGNINSTRUCTION_H
#define XLANG_ASSIGNINSTRUCTION_H

#include "Instruction.h"
#include "../../interpreter/Variable.h"
#include "../../interpreter/Data.h"

namespace xlang {
    namespace compiler {
        namespace instructions {

            class AssignInstruction : public Instruction {
            private:
                const interpreter::Variable *target;
                const interpreter::Data *data;

            public:
                AssignInstruction(const interpreter::Variable &_target, const interpreter::Data &_data) : target(&_target), data(&_data) {}

                const interpreter::Variable *getTarget() const {
                    return target;
                }

                void setTarget(const interpreter::Variable *target) {
                    AssignInstruction::target = target;
                }

                const interpreter::Data *getData() const {
                    return data;
                }

                void setData(const interpreter::Data *data) {
                    AssignInstruction::data = data;
                }
            };
        }
    }
}

#endif //XLANG_ASSIGNINSTRUCTION_H
