//
// Created by Nils van Eijk on 22-03-18.
//

#include "Scope.h"

using namespace std;

void Scope::Parse(TokenParser &parser) {
    while(true) {
        auto token = parser.getToken(false);

        if (token == L"{") {
            auto scope = parseNestedScope(parser);
            scopes.push_back(std::move(scope));
        } else if (token == L"}") {
            break;
        } else if (Variable::isVariableType(token)) {

        }
    }

    // TODO: Return?
}

std::unique_ptr<Scope> Scope::parseNestedScope(TokenParser &parser) {
    auto result = make_unique<Scope>();
    result->Parse(parser);
    return result;
}
