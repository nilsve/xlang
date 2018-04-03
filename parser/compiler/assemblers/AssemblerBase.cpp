//
// Created by Nils van Eijk on 30-03-18.
//

#include "AssemblerBase.h"

std::wstring AssemblerBase::assembleFunctionStart(const Function &function) const {
    return function.getParent()->getModuleName() + L"_" + function.getFunctionName() + L":";
}

std::wstring AssemblerBase::assembleScopeStart(const Scope &scope) const {
    return scope.getParentFunction()->getParent()->getModuleName() + L"_" + scope.getParentFunction()->getFunctionName() + L"_" + scope.getScopeId();
}