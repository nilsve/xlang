//
// Created by Nils van Eijk on 02-03-18.
//

#include "Module.h"
#include "Function.h"

#include <memory>
#include <cassert>

using namespace std;

namespace xlang {
    namespace interpreter {

        void Module::Parse(TokenParser &parser) {
            assert(parser.getToken() == L"module");

            auto moduleName = parser.getToken(true);

            this->moduleName = moduleName.token;

            if (parser.getToken() != L"{") {
                parser.throwError("Expected { after module name");
            }

            while (true) {
                auto token = parser.peekToken();

                if (token == L"}") {
                    parser.eatToken();
                    break;
                } else if (token == L"FUNCTION") {
                    parseFunction(parser);
                } else if (Variable::isVariableType(token)) {
                    parseVariable(parser);
                } else {
                    return parser.throwError(L"Unexpected token " + token.token);
                }
            }
        }

        void Module::parseVariable(TokenParser &parser) {
            auto variable = make_unique<Variable>();
            variable->Parse(parser);
            variables.push_back(std::move(variable));
        }

        void Module::parseFunction(TokenParser &parser) {
            auto function = make_unique<Function>(this);
            function->Parse(parser);
            functions.push_back(std::move(function));
        }

        std::wstring Module::getModuleName() const {
            return moduleName;
        }

        const std::vector<std::unique_ptr<Function>> &Module::getFunctions() const {
            return functions;
        }

        const std::vector<std::unique_ptr<Variable>> &Module::getVariables() const {
            return variables;
        }
    }
}