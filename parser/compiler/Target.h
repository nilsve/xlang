//
// Created by Nils van Eijk on 04-04-18.
//

#ifndef XLANG_TARGET_H
#define XLANG_TARGET_H

#include <string>
#include "../interpreter/Function.h"

namespace xlang {
    namespace compiler {

        class Target : public utils::non_copyable {
        private:
            interpreter::CallingConvention callingConvention;
        public:
            virtual std::wstring getModuleName() const = 0;

            interpreter::CallingConvention getCallingConvention() const;

            void setCallingConvention(interpreter::CallingConvention callingConvention);

            virtual std::wstring getFunctionName() const = 0;

            virtual std::wstring getScopeId() const = 0;

            virtual std::wstring getFullPath() const = 0;
        };
    }
}

#endif //XLANG_TARGET_H
