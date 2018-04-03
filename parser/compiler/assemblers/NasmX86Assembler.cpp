//
// Created by Nils van Eijk on 30-03-18.
//

#include "NasmX86Assembler.h"
#include "../instructions/CallInstruction.h"
#include "../instructions/AssignInstruction.h"

#include <iostream>

const unsigned long REGISTER_SIZE = 4;

std::wstring NasmX86Assembler::assembleInstruction(const Instruction& instruction) const {
    if (auto callInstruction = dynamic_cast<const CallInstruction*>(&instruction)) {

        for (auto& parameter : callInstruction->getParameters()) {

        }

        return L"call " + callInstruction->getTarget();
    } else if (auto assignInstruction = dynamic_cast<const AssignInstruction*>(&instruction)) {
        auto target = assignInstruction->getTarget();
        if (!target) {
            Utils::throwError("Target empty for assignment instruction!");
        }

        return L"mov [ebp + " + std::to_wstring(target->getVariableIndex() * REGISTER_SIZE) + L"], 0";
    }

    throw std::invalid_argument("Instruction not implemented!");
}

std::wstring NasmX86Assembler::assembleFunctionEnd() const {
    return  L"mov esp, ebp\n"
            L"pop ebp\n"
            L"ret";
}

std::wstring NasmX86Assembler::assembleScopeStart(const Scope &scope) const {
    auto result = AssemblerBase::assembleScopeStart(scope);

    unsigned int scopeReservation = scope.getVariables().size() * REGISTER_SIZE;
    if (scopeReservation > 0) {
        result +=   L"\n"
                    L"sub esp, " + std::to_wstring(scopeReservation);
    }

    return result;
}

std::wstring NasmX86Assembler::assembleFunctionStart(const Function &function) const {
    auto result = AssemblerBase::assembleFunctionStart(function);
    result +=   L"\n"
                L"push ebp\n"
                L"mov ebp, esp";
    return result;
}

std::wstring NasmX86Assembler::assembleScopeEnd(const Scope& scope) const {
    auto result = AssemblerBase::assembleScopeStart(scope);

    unsigned int scopeReservation = scope.getVariables().size() * REGISTER_SIZE;
    if (scopeReservation > 0) {
        result += L"\n"
                  L"add esp, " + std::to_wstring(scopeReservation);
    }

    return result;
}

