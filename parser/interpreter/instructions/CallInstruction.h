//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_CALLNSTRUCTION_H
#define XLANG_CALLNSTRUCTION_H


#include "../../../utils/non_copyable.h"
#include "Instruction.h"
#include "../Variable.h"

#include <memory>
#include <vector>

class CallInstruction : public non_copyable {
private:
    std::wstring targetFunction;
    std::vector<const Variable*> parameters;

public:
    CallInstruction(std::wstring _targetFunction, std::vector<const Variable*> _parameters) : targetFunction(std::move(_targetFunction)), parameters(std::move(_parameters)) {}
};


#endif //XLANG_CALLNSTRUCTION_H
