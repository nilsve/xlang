//
// Created by Nils van Eijk on 04-04-18.
//

#ifndef XLANG_STRONGTARGET_H
#define XLANG_STRONGTARGET_H


#include "Target.h"

#include <string>

enum class StrongTargetType {
    scope,
    function,
};

class Scope;
class Function;

class StrongTarget : public Target {
private:
    StrongTargetType type;
    union {
        const Scope* scope;
        const Function* function;
    } target;

    const Function& getFunction() const;

    std::wstring getPath(const Scope *scope) const;
    std::wstring getPath(const Function *function) const;
public:
    explicit StrongTarget(const Scope& scope) {
        type = StrongTargetType::scope;
        target.scope = &scope;
    }

    explicit StrongTarget(const Function& function) {
        type = StrongTargetType::function;
        target.function = &function;
    }

    std::wstring getModuleName() const override;
    std::wstring getFunctionName() const override;
    std::wstring getScopeId() const override;
    std::wstring getFullPath() const override;
};


#endif //XLANG_STRONGTARGET_H
