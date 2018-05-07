//
// Created by Nils van Eijk on 02-03-18.
//

#ifndef XLANG_MODULE_H
#define XLANG_MODULE_H

#include <string>
#include "TokenParser.h"
#include "Function.h"
#include "Variable.h"
#include "Container.h"
#include <vector>

namespace xlang {
    namespace interpreter {

        class Module : public Container, public utils::non_copyable {
        private:
            std::wstring moduleName;
            std::vector<std::unique_ptr<Function>> functions;

            void parseFunction(TokenParser &parser);

            void parseVariable(TokenParser &parser);

        public:
            void Parse(TokenParser &parser) override;

            std::wstring getModuleName() const;

            const std::vector<std::unique_ptr<Function>> &getFunctions() const;
        };
    }
}

#endif //XLANG_MODULE_H
