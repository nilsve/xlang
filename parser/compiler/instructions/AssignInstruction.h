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

            enum class ArithmeticType {
                ASSIGN,
                DIVIDE,
                MULTIPLY,
                SUBSTRACT,
                ADD,
            };



            class AssignInstruction : public Instruction {
            private:
                const interpreter::Variable *target = nullptr;
                const interpreter::Data *data = nullptr;
                const interpreter::Variable *sourceVariable = nullptr;

                ArithmeticType arithmeticOperation = ArithmeticType::ASSIGN;

            public:
                AssignInstruction(const interpreter::Variable &_target, const interpreter::Data &_data) : target(&_target), data(&_data) {}
                AssignInstruction(const interpreter::Variable &_target, const interpreter::Variable &_sourceVariable) : target(&_target), sourceVariable(&_sourceVariable) {}

                const interpreter::Variable *getTarget() const {
                    return target;
                }

                ArithmeticType getArithmeticOperation() const {
                    return arithmeticOperation;
                }

                void setArithmeticOperation(ArithmeticType arithmeticOperation) {
                    AssignInstruction::arithmeticOperation = arithmeticOperation;
                }

                const interpreter::Data *getData() const {
                    return data;
                }

                const interpreter::Variable *getSourceVariable() const {
                    return sourceVariable;
                }
            };
        }
    }
}

#endif //XLANG_ASSIGNINSTRUCTION_H
