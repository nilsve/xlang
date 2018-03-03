//
// Created by Nils van Eijk on 02-03-18.
//

#include "Module.h"

#include <memory>

using namespace std;

void Module::Parse(TokenParser& parser) {
    auto moduleName = parser.getToken();

    if (!moduleName.isStringLiteral) {
        return parser.throwError("Expected string literal after module declaration!");
    }

    this->moduleName = moduleName.token;

    while(true) {
        auto token = parser.getToken();

        if (token.token == L"function") {
            parseFunction(parser);
        } else {
            return parser.throwError(L"Unexpected token " + token.token);
        }
    }
}

void Module::parseFunction(TokenParser& parser) {
    shared_ptr<Module> module = make_shared<Module>();
    module->Parse(parser);
    modules.push_back(module);
}
