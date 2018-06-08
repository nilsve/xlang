//
// Created by Nils van Eijk on 30-05-18.
//

#ifndef XLANG_VARIABLELINK_H
#define XLANG_VARIABLELINK_H

#include "Variable.h"

namespace xlang {
    namespace interpreter {
        class VariableLink {
        public:
            const Variable& variable;
            bool dereference;

            VariableLink(const Variable& _variable, bool _dereference) : variable(_variable), dereference(_dereference) {}
        };
    }
}

#endif //XLANG_VARIABLELINK_H
