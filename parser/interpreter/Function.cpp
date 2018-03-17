//
// Created by Nils van Eijk on 02-03-18.
//

#include "Function.h"

void Function::Parse(TokenParser &parser) {
    auto functionName = parser.getToken();

    if (!functionName.isStringLiteral) {
        return parser.throwError("Expected string literal after function declaration!");
    }

    this->functionName = functionName.token;

    while(true) {
        auto token = parser.getToken(false);

        if (token.token != L"(") {
            parser.throwError("Expected ( after function name");
        }

        token = parser.getToken(false);

        if (token.token != L")")
        {
            // Parameters
        }
    }
}
