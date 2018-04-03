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
public:
    const std::wstring moduleName;
    const std::wstring functionName;
    const std::wstring scopeId;
    const std::vector<const Variable*> parameters;

    CallInstruction(std::wstring _moduleName, std::wstring _functionName, std::wstring _scopeId, std::vector<const Variable*> _parameters) : moduleName(std::move(_moduleName)),
                                                                                                                                             functionName(std::move(_functionName)),
                                                                                                                                             scopeId(std::move(_scopeId)),
                                                                                                                                             parameters(std::move(_parameters)) {}
    CallInstruction(std::wstring _moduleName, std::wstring _functionName, std::wstring _scopeId) : moduleName(std::move(_moduleName)),
                                                                                                   functionName(std::move(_functionName)),
                                                                                                   scopeId(std::move(_scopeId)) {}

    std::wstring getTarget() const {
        std::wstring target;
        if (moduleName.length()) {
            target += moduleName;
        }
        if (functionName.length()) {
            target += L"_" + functionName;
        }
        if (scopeId.length()) {
            target += L"_" + scopeId;
        }

        return target;
    }

    const std::vector<const Variable *> &getParameters() const {
        return parameters;
    }
};

#endif //XLANG_CALLNSTRUCTION_H
