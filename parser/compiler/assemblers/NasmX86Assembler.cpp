//
// Created by Nils van Eijk on 30-03-18.
//

#include "NasmX86Assembler.h"
#include "../instructions/CallInstruction.h"
#include "../instructions/AssignInstruction.h"
#include "../instructions/JmpInstruction.h"

#include <iostream>

const unsigned long REGISTER_SIZE = 4;

std::wstring NasmX86Assembler::assembleInstruction(const Instruction& instruction) const {
    if (auto callInstruction = dynamic_cast<const CallInstruction*>(&instruction)) {

        for (auto& parameter : callInstruction->getParameters()) {

        }

        return L"call " + callInstruction->getTarget()->getFullPath();
    } else if (auto assignInstruction = dynamic_cast<const AssignInstruction*>(&instruction)) {

        if (auto target = assignInstruction->getTarget()) {
            return L"mov [ebp + " + std::to_wstring(target->getVariableIndex() * REGISTER_SIZE) + L"], 0";
        } else {
            Utils::throwError("Target empty for assignment instruction!");
        }
    } else if (auto jmpInstruction = dynamic_cast<const JmpInstruction*>(&instruction)) {
        return L"jmp " + jmpInstruction->getTarget();
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
    std::wstring result = L"ret";

    unsigned int scopeReservation = scope.getVariables().size() * REGISTER_SIZE;
    if (scopeReservation > 0) {
        result  = L"add esp, " + std::to_wstring(scopeReservation) + L"\n" + result;
    }

    return result;
}

std::wstring NasmX86Assembler::assembleData(const Data &data) const {
    auto result = data.getDataId() +   L":\n";

    auto& bytes = data.getData();

    result.reserve(bytes.size() + result.size());
    for (auto chr : data.getData()) {
        result += chr;
    }
}

