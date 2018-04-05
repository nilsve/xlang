//
// Created by Nils van Eijk on 02-03-18.
//

#ifndef XLANG_MODULE_H
#define XLANG_MODULE_H

#include <string>
#include "TokenParser.h"
#include "Function.h"
#include "Variable.h"
#include <vector>

namespace xlang {
    namespace interpreter {

        class Module : public utils::non_copyable {
        private:
            std::wstring moduleName;
            std::vector<std::unique_ptr<Function>> functions;
            std::vector<std::unique_ptr<Variable>> variables;

            void parseFunction(TokenParser &parser);

            void parseVariable(TokenParser &parser);

        public:
            void Parse(TokenParser &parser);

            std::wstring getModuleName() const;

            const std::vector<std::unique_ptr<Function>> &getFunctions() const;

            const std::vector<std::unique_ptr<Variable>> &getVariables() const;
        };
    }
}

#endif //XLANG_MODULE_H
