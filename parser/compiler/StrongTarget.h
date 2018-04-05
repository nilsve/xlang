//
// Created by Nils van Eijk on 04-04-18.
//

#ifndef XLANG_STRONGTARGET_H
#define XLANG_STRONGTARGET_H


#include "Target.h"

#include <string>

namespace xlang {

    namespace interpreter {
        class Scope;
        class Function;
    }

    namespace compiler {

        enum class StrongTargetType {
            scope,
            function,
        };



        class StrongTarget : public Target {
        private:
            StrongTargetType type;
            union {
                const interpreter::Scope *scope;
                const interpreter::Function *function;
            } target;

            const interpreter::Function &getFunction() const;

            std::wstring getPath(const interpreter::Scope *scope) const;

            std::wstring getPath(const interpreter::Function *function) const;

        public:
            explicit StrongTarget(const interpreter::Scope &scope) {
                type = StrongTargetType::scope;
                target.scope = &scope;
            }

            explicit StrongTarget(const interpreter::Function &function) {
                type = StrongTargetType::function;
                target.function = &function;
            }

            std::wstring getModuleName() const override;

            std::wstring getFunctionName() const override;

            std::wstring getScopeId() const override;

            std::wstring getFullPath() const override;
        };
    }
}


#endif //XLANG_STRONGTARGET_H
