//
// Created by Nils van Eijk on 30-03-18.
//

#ifndef XLANG_ASSEMBLERBASE_H
#define XLANG_ASSEMBLERBASE_H

#include <string>
#include "../instructions/Instruction.h"
#include "../../interpreter/Function.h"
#include "../../interpreter/Module.h"

namespace xlang {
    namespace compiler {
        namespace assemblers {

            class AssemblerBase {
            public:
                virtual std::wstring assembleInstruction(const compiler::instructions::Instruction &instruction) const = 0;

                virtual std::wstring assembleFunctionEnd(const interpreter::Function &function) const = 0;

                virtual std::wstring assembleScopeEnd(const interpreter::Scope &scope) const = 0;

                virtual std::wstring assembleData(const interpreter::Data &data) const = 0;

                virtual std::wstring assembleFunctionStart(const interpreter::Function &function) const {
                    return function.getParent()->getId() + L"_" + function.getId() + L":";
                };

                virtual std::wstring assembleScopeStart(const interpreter::Scope &scope) const {
                    return scope.getParentFunction()->getParent()->getId() + L"_" +
                           scope.getParentFunction()->getId() + L"_" + scope.getId() + L":";
                };
            };
        }
    }
}

#endif //XLANG_ASSEMBLERBASE_H
