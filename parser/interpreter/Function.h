//
// Created by Nils van Eijk on 02-03-18.
//

#ifndef XLANG_FUNCTION_H
#define XLANG_FUNCTION_H


#include "TokenParser.h"
#include "Variable.h"
#include "Scope.h"

#include <memory>
#include <vector>

namespace xlang {
    namespace interpreter {

        enum class CallingConvention {
            CDECL,
            STDCALL,
            UNKNOWN,
        };

        class Module;

        class Function : public Container, public utils::non_copyable {
        private:
            CallingConvention callingConvention;

            std::vector<std::unique_ptr<Variable>> parameters;
            std::unique_ptr<Variable> returnVariable;

            std::unique_ptr<Scope> rootScope;

            void parseHeader(TokenParser &parser);

            void parseBody(TokenParser &parser);

            static CallingConvention getCallingConvention(const std::wstring &convention);

        public:
            explicit Function(const Container *_parent) : Container(L"", _parent) {}

            void Parse(TokenParser &parser) override;

            CallingConvention getCallingConvention() const;

            const std::vector<std::unique_ptr<Variable>> &getParameters() const;

            const std::unique_ptr<Variable> &getReturnVariable() const;

            const std::unique_ptr<Scope> &getRootScope() const;
        };
    }
}

#endif //XLANG_FUNCTION_H
