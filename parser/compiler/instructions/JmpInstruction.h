//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_JMPINSTRUCTION_H
#define XLANG_JMPINSTRUCTION_H

#include "Instruction.h"

#include <memory>

class JmpInstruction : public Instruction {
private:
    Instruction* targetScope;
public:
    explicit JmpInstruction(Instruction* _targetScope) : targetScope(_targetScope) {}
};


#endif //XLANG_JMPINSTRUCTION_H
