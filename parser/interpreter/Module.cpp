//
// Created by Nils van Eijk on 02-03-18.
//

#include "Module.h"
#include "Function.h"

#include <memory>

using namespace std;

void Module::Parse(TokenParser& parser) {
    auto moduleName = parser.getToken();

    if (!moduleName.isStringLiteral) {
        return parser.throwError("Expected string literal after module declaration!");
    }

    this->moduleName = moduleName.token;

    while(true) {
        auto token = parser.getToken(false);

        if (token.token == L"function") {
            parseFunction(parser);
        } else if (Variable::isVariableType(token.token)) {
            parseVariable(parser, token);
        } else {
            return parser.throwError(L"Unexpected token " + token.token);
        }
    }
}

void Module::parseVariable(TokenParser& parser, const Token& dataType) {
    auto variable = make_shared<Variable>(dataType.token);
    variable->Parse(parser);
    variables.push_back(variable);
}

void Module::parseFunction(TokenParser& parser) {
    auto function = make_shared<Function>();
    function->Parse(parser);
    functions.push_back(function);
}
