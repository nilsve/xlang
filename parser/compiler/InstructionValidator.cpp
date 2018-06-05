//
// Created by Nils van Eijk on 31-03-18.
//

#include "InstructionValidator.h"
#include "WeakTarget.h"
#include "instructions/JmpInstruction.h"
#include "../interpreter/Scope.h"

namespace xlang {
    namespace compiler {

        using namespace instructions;
        using namespace utils;

        void InstructionValidator::validateAndPatchInstruction(Instruction &instruction) const {
            if (auto callInstruction = dynamic_cast<CallInstruction *>(&instruction)) {
                handleTarget(instruction, *callInstruction->getTarget());
            } else if (auto jmpInstruction = dynamic_cast<JmpInstruction *>(&instruction)) {
                handleTarget(instruction, *jmpInstruction->getTarget());
            }
        }

        bool InstructionValidator::findScopeId(const interpreter::Scope &rootScope, std::wstring scopeId) const {
            if (rootScope.getId() == scopeId) {
                return true;
            } else {
                auto &scopes = rootScope.getScopes();
                for (auto &scope : scopes) {
                    if (findScopeId(*scope, scopeId)) {
                        return true;
                    }
                }
            }

            return false;
        }

        void InstructionValidator::handleTarget(const Instruction &instruction, Target &target) const {

            if (auto weakTarget = dynamic_cast<const WeakTarget *>(&target)) {
                if (!weakTarget->getModuleName().length()) {
                    return;
                }

                for (auto &module : parser.getModules()) {
                    if (module->getId() == weakTarget->getModuleName()) {
                        if (!weakTarget->getFunctionName().length()) {
                            return;
                        }

                        for (auto &function : module->getFunctions()) {
                            if (weakTarget->getFunctionName() == function->getId()) {
                                target.setCallingConvention(function->getCallingConvention());

                                if (auto callInstruction = dynamic_cast<const CallInstruction *>(&instruction)) {
                                    if (callInstruction->getParameters().size() != function->getParameters().size()) {
                                        Utils::throwError("Parameter count doesn't match!"); //TODO: Lijn etc
                                    } else {
                                        auto &arguments = callInstruction->getParameters();
                                        auto &parameters = function->getParameters();
                                        for (unsigned int i = 0; i < arguments.size(); i++) {
                                            if (arguments[i].variable.getDataType() != parameters[i]->getDataType()) {
                                                Utils::throwError(
                                                        L"Invalid argument supplied to " + function->getId());
                                            }
                                        }
                                    }
                                }

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

                Utils::throwError(L"Unknown function / scope " + target.getFullPath());
            }
        }
    }
}