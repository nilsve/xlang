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
                const interpreter::Variable *target = nullptr;
                const interpreter::Data *data = nullptr;
                const interpreter::Variable *sourceVariable = nullptr;
                const std::unique_ptr<interpreter::Variable> constSimpleType;

            public:
                AssignInstruction(const interpreter::Variable &_target, const interpreter::Data &_data) : target(&_target), data(&_data) {}
                AssignInstruction(const interpreter::Variable &_target, const interpreter::Variable &_sourceVariable) : target(&_target), sourceVariable(&_sourceVariable) {}
                AssignInstruction(const interpreter::Variable &_target, std::unique_ptr<interpreter::Variable> _constSimpleType): target(&_target), constSimpleType(std::move(_constSimpleType)) {}

                const interpreter::Variable *getTarget() const {
                    return target;
                }

                void setTarget(const interpreter::Variable *target) {
                    AssignInstruction::target = target;
                }

                const interpreter::Data *getData() const {
                    return data;
                }

                const interpreter::Variable *getSourceVariable() const {
                    return sourceVariable;
                }

                void setData(const interpreter::Data *data) {
                    AssignInstruction::data = data;
                }

                const std::unique_ptr<interpreter::Variable> &getConstSimpleType() const {
                    return constSimpleType;
                }
            };
        }
    }
}

#endif //XLANG_ASSIGNINSTRUCTION_H
