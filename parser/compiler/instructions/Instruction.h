//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_INSTRUCTION_H
#define XLANG_INSTRUCTION_H


#include "../../../utils/non_copyable.h"

namespace xlang {
    namespace compiler {
        namespace instructions {

            class Instruction : public utils::non_copyable {
            public:
                virtual ~Instruction() = default;
            };
        }
    }
}

#endif //XLANG_INSTRUCTION_H
