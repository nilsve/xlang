//
// Created by Nils van Eijk on 04-04-18.
//

#ifndef XLANG_WEAKTARGET_H
#define XLANG_WEAKTARGET_H

#include "Target.h"

#include <string>

class WeakTarget : public Target {
    std::wstring moduleName;
    std::wstring functionName;
    std::wstring scopeId;
public:
    WeakTarget(std::wstring _moduleName, std::wstring _functionName) : moduleName(std::move(_moduleName)), functionName(std::move(_functionName)) {}
    WeakTarget(std::wstring _moduleName, std::wstring _functionName, std::wstring _scopeId) : moduleName(std::move(_moduleName)), functionName(std::move(_functionName)), scopeId(std::move(_scopeId)) {}

    std::wstring getModuleName() const override;
    std::wstring getFunctionName() const override;
    std::wstring getScopeId() const override;
    std::wstring getFullPath() const override;
};


#endif //XLANG_WEAKTARGET_H
