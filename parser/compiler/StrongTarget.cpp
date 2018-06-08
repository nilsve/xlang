//
// Created by Nils van Eijk on 04-04-18.
//

#include "StrongTarget.h"

#include "../interpreter/Module.h"
#include "../interpreter/Function.h"
#include "../interpreter/Scope.h"

#include <cassert>

namespace xlang {
    namespace compiler {

        using namespace interpreter;

        std::wstring StrongTarget::getModuleName() const {
            return getFunction().getParent()->getId();
        }

        std::wstring StrongTarget::getFunctionName() const {
            return getFunction().getId();
        }

        std::wstring StrongTarget::getScopeId() const {
            if (type == StrongTargetType::SCOPE) {
                return target.scope->getId();
            }
            return L"";
        }

        const Function &StrongTarget::getFunction() const {
            const Function *function = nullptr;
            if (type == StrongTargetType::SCOPE) {
                function = target.scope->getParentFunction();
            } else {
                function = target.function;
            }

            assert(function);
            return *function;
        }


        std::wstring StrongTarget::getFullPath() const {

            switch (type) {
                case StrongTargetType::SCOPE:
                    assert(target.scope);
                    return getPath(target.scope);
                case StrongTargetType::FUNCTION:
                    assert(target.function);
                    return getPath(target.function);
            }

            assert(false);
        }

        std::wstring StrongTarget::getPath(const Scope *scope) const {
            std::wstring result = scope->getId();
            if (auto function = scope->getParentFunction()) {
                result = getPath(function) + L"_" + result;
            }

            return result;
        }

        std::wstring StrongTarget::getPath(const Function *function) const {
            std::wstring result = function->getId();
            if (auto module = function->getParent()) {
                result = module->getId() + L"_" + result;
            }

            return result;
        }
    }
}