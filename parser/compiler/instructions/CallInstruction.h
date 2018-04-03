//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_CALLNSTRUCTION_H
#define XLANG_CALLNSTRUCTION_H


#include "Instruction.h"
#include "../../interpreter/Variable.h"

#include <memory>
#include <vector>

class CallInstruction : public Instruction {
private:
    std::wstring target;
    std::vector<const Variable*> parameters;

public:
    CallInstruction(std::wstring _target, std::vector<const Variable*> _parameters) : target(std::move(_target)), parameters(std::move(_parameters)) {}
    CallInstruction(std::wstring _target) : target(std::move(_target)) {}

    const std::wstring& getTarget() const {
        return target;
    }

    const std::vector<const Variable *> &getParameters() const {
        return parameters;
    }
};

#endif //XLANG_CALLNSTRUCTION_H
