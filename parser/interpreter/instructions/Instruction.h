//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_INSTRUCTION_H
#define XLANG_INSTRUCTION_H


#include "../../../utils/non_copyable.h"

class Instruction : public non_copyable {
public:
    virtual void Assemble() = 0;
};


#endif //XLANG_INSTRUCTION_H
