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
    std::vector<std::weak_ptr<Variable>> parameters;

public:
    CallInstruction(std::wstring _targetFunction, std::vector<std::weak_ptr<Variable>> _parameters) : targetFunction(_targetFunction), parameters(_parameters) {}

};


#endif //XLANG_CALLNSTRUCTION_H
