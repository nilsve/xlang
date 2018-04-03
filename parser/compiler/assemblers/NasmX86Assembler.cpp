//
// Created by Nils van Eijk on 30-03-18.
//

#include "NasmX86Assembler.h"
#include "../instructions/CallInstruction.h"

#include <iostream>

std::wstring NasmX86Assembler::assembleInstruction(const Instruction& instruction) const {
    if (auto callInstruction = dynamic_cast<const CallInstruction*>(&instruction)) {

        for (auto& parameter : callInstruction->getParameters()) {

        }

        return L"call " + callInstruction->getTarget();
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

    unsigned int scopeReservation = scope.getVariables().size() * 4;
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

    unsigned int scopeReservation = scope.getVariables().size() * 4;
    if (scopeReservation > 0) {
        result += L"\n"
                  L"add esp, " + std::to_wstring(scopeReservation);
    }

    return result;
}

