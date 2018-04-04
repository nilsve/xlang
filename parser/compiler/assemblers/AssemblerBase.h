//
// Created by Nils van Eijk on 30-03-18.
//

#ifndef XLANG_ASSEMBLERBASE_H
#define XLANG_ASSEMBLERBASE_H

#include <string>
#include "../instructions/Instruction.h"
#include "../../interpreter/Function.h"
#include "../../interpreter/Module.h"

class AssemblerBase {
public:
    virtual std::wstring assembleInstruction(const Instruction& instruction) const = 0;
    virtual std::wstring assembleFunctionEnd() const = 0;
    virtual std::wstring assembleScopeEnd(const Scope& scope) const = 0;
    virtual std::wstring assembleData(const Data& data) const = 0;

    virtual std::wstring assembleFunctionStart(const Function & function) const {
        return function.getParent()->getModuleName() + L"_" + function.getFunctionName() + L":";
    };

    virtual std::wstring assembleScopeStart(const Scope& scope) const {
        return scope.getParentFunction()->getParent()->getModuleName() + L"_" + scope.getParentFunction()->getFunctionName() + L"_" + scope.getScopeId();
    };
};


#endif //XLANG_ASSEMBLERBASE_H
