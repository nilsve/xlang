//
// Created by Nils van Eijk on 30-03-18.
//

#ifndef XLANG_NASMASSEMBLER_H
#define XLANG_NASMASSEMBLER_H


#include "AssemblerBase.h"

class NasmAssembler : public AssemblerBase {
public:
    void assembleInstruction();
};


#endif //XLANG_NASMASSEMBLER_H
