//
// Created by Nils van Eijk on 21-03-18.
//

#ifndef XLANG_STRUCTURE_H
#define XLANG_STRUCTURE_H


#include "../../utils/non_copyable.h"

#include <string>

namespace xlang {
    namespace interpreter {

        class Structure : public utils::non_copyable {
            std::wstring structureName;

        };
    }
}

#endif //XLANG_STRUCTURE_H
