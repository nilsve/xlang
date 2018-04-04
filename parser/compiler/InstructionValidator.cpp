//
// Created by Nils van Eijk on 31-03-18.
//

#include "InstructionValidator.h"
#include "WeakTarget.h"

void InstructionValidator::validateInstruction(const Instruction &instruction) const {
    if (auto callInstruction = dynamic_cast<const CallInstruction *>(&instruction)) {
        validateCallInstruction(*callInstruction);
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

void InstructionValidator::validateCallInstruction(const CallInstruction &callInstruction) const {

    if (auto weakTarget = dynamic_cast<const WeakTarget*>(callInstruction.getTarget())) {
        if (!weakTarget->getModuleName().length()) {
            return;
        }

        for (auto &module : parser.getModules()) {
            if (module->getModuleName() == weakTarget->getModuleName()) {
                if (!weakTarget->getFunctionName().length()) {
                    return;
                }

                for (auto &function : module->getFunctions()) {
                    if (weakTarget->getFunctionName() == function->getFunctionName()) {
                        if (!weakTarget->getScopeId().length()) {
                            return;
                        }

                        if (findScopeId(*function->getRootScope(), weakTarget->getScopeId())) {
                            return;
                        }
                    }
                }
            }
        }

        Utils::throwError(L"Unknown function / scope " + callInstruction.getTarget()->getFullPath());
    }

}
