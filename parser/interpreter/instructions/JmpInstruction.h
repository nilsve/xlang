//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_JMPINSTRUCTION_H
#define XLANG_JMPINSTRUCTION_H

#include "Instruction.h"

#include <memory>

class JmpInstruction : public Instruction {
private:
    std::weak_ptr<Instruction> targetScope;
public:
    JmpInstruction(std::shared_ptr<Instruction> _targetScope) : targetScope(_targetScope) {}
    void Assemble();
};


#endif //XLANG_JMPINSTRUCTION_H
