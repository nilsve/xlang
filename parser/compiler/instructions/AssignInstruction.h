//
// Created by Nils van Eijk on 03-04-18.
//

#ifndef XLANG_ASSIGNINSTRUCTION_H
#define XLANG_ASSIGNINSTRUCTION_H

#include "Instruction.h"
#include "../../interpreter/Variable.h"
#include "../../interpreter/Data.h"

class AssignInstruction : public Instruction {
private:
    const Variable* target;
    const Data* data;

public:
    AssignInstruction(const Variable& _target, const Data& _data) : target(&_target), data(&_data) {}
};

#endif //XLANG_ASSIGNINSTRUCTION_H
