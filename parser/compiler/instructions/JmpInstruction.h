//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_JMPINSTRUCTION_H
#define XLANG_JMPINSTRUCTION_H

#include "Instruction.h"

#include <memory>

class JmpInstruction : public Instruction {
private:
    const Instruction* targetScope;
public:
    explicit JmpInstruction(Instruction* _targetScope) : targetScope(_targetScope) {}

    const Instruction *getTargetScope() const {
        return targetScope;
    }
};


#endif //XLANG_JMPINSTRUCTION_H
