//
// Created by Nils van Eijk on 04-04-18.
//

#include "../interpreter/Function.h"
#include "Target.h"

CallingConvention Target::getCallingConvention() const {
    return callingConvention;
}

void Target::setCallingConvention(CallingConvention callingConvention) {
    Target::callingConvention = callingConvention;
}
