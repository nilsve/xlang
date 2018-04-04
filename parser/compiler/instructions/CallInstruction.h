//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_CALLNSTRUCTION_H
#define XLANG_CALLNSTRUCTION_H


#include "Instruction.h"
#include "../../interpreter/Variable.h"
#include "../Target.h"

#include <memory>
#include <vector>

class CallInstruction : public Instruction {
private:
    const std::unique_ptr<Target> target;
    const std::vector<const Variable*> parameters;
public:
    CallInstruction(std::unique_ptr<Target> _target, std::vector<const Variable*> _parameters) : target(std::move(_target)), parameters(std::move(_parameters)) {}
    CallInstruction(std::unique_ptr<Target> _target) : target(std::move(_target)) {}

    Target* getTarget() const {
        return target.get();
    }

    const std::vector<const Variable *> &getParameters() const {
        return parameters;
    }
};

#endif //XLANG_CALLNSTRUCTION_H
