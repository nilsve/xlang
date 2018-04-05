//
// Created by Nils van Eijk on 04-04-18.
//

#include "WeakTarget.h"

namespace xlang {
    namespace compiler {
        std::wstring WeakTarget::getModuleName() const {
            return moduleName;
        }

        std::wstring WeakTarget::getFunctionName() const {
            return functionName;
        }

        std::wstring WeakTarget::getScopeId() const {
            return scopeId;
        }

        std::wstring WeakTarget::getFullPath() const {
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
    }
}