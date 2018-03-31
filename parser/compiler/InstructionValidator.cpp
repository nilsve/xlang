//
// Created by Nils van Eijk on 31-03-18.
//

#include "InstructionValidator.h"

void InstructionValidator::validateInstruction(const Instruction &instruction) const {
    if (auto callInstruction = dynamic_cast<const CallInstruction *>(&instruction)) {
        if (!callInstruction->moduleName.length()) {
            return;
        }

        auto &modules = parser.getModules();
        for (auto &module : modules) {
            if (module->getModuleName() == callInstruction->moduleName) {
                if (!callInstruction->functionName.length()) {
                    return;
                }
                auto &functions = module->getFunctions();
                for (auto &function : functions) {
                    if (function->getFunctionName() == callInstruction->functionName) {
                        if (!callInstruction->scopeId.length()) {
                            return;
                        }

                        if (findScopeId(*function->getRootScope(), callInstruction->scopeId)) {
                            return;
                        }

                        break;
                    }
                }

                break;
            }
        }

        Utils::throwError(L"Unknown function / scope " + callInstruction->getTarget());

    }
}

bool InstructionValidator::findScopeId(const Scope &rootScope, std::wstring scopeId) const {
    if (rootScope.getScopeId() == scopeId) {
        return true;
    } else {
        auto& scopes = rootScope.getScopes();
        for (auto& scope : scopes) {
            if (findScopeId(*scope, scopeId)) {
                return true;
            }
        }
    }

    return false;
}
