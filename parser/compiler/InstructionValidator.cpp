//
// Created by Nils van Eijk on 31-03-18.
//

#include "InstructionValidator.h"

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
    if (!callInstruction.moduleName.length()) {
        return;
    }

    for (auto &module : parser.getModules()) {
        if (module->getModuleName() == callInstruction.moduleName) {
            if (!callInstruction.functionName.length()) {
                return;
            }
            for (auto &function : module->getFunctions()) {
                if (function->getFunctionName() == callInstruction.functionName) {
                    if (!callInstruction.scopeId.length()) {
                        return;
                    }

                    if (findScopeId(*function->getRootScope(), callInstruction.scopeId)) {
                        return;
                    }

                    break;
                }
            }

            break;
        }
    }

    Utils::throwError(L"Unknown function / scope " + callInstruction.getTarget());

}
