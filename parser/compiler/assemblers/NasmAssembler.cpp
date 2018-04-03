//
// Created by Nils van Eijk on 30-03-18.
//

#include "NasmAssembler.h"
#include "../instructions/CallInstruction.h"

#include <iostream>

std::wstring NasmAssembler::assembleInstruction(const Instruction& instruction) const {
    if (auto callInstruction = dynamic_cast<const CallInstruction*>(&instruction)) {

        for (auto& parameter : callInstruction->getParameters()) {

        }

        return L"call " + callInstruction->getTarget();
    }

    throw std::invalid_argument("Instruction not implemented!");
}

std::wstring NasmAssembler::assembleFunctionEnd() const {
    return L"ret";
}
