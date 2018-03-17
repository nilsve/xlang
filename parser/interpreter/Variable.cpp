//
// Created by Nils van Eijk on 08-03-18.
//

#include "Variable.h"

#include <set>
#include <string>
#include <sstream>

using namespace std;

bool Variable::isVariableType(const std::wstring &token, bool isFunctionArgument) {
    static set<wstring> dataTypes = {
        L"char",
        L"int"
    };

    return dataTypes.find(token) != dataTypes.end();
}

void Variable::Parse(TokenParser &parser) {
    auto token = parser.getToken(false);

    if (token.token == L"[") {
        isArray = true;

        token = parser.getToken(false);

        if (token.token == L"]") {
            // Array of yet unknown length
        } else {
            std::wstringstream ss(token.token);
            if ((ss >> arrayLength).fail() || !(ss >> std::ws).eof())
            {
                return parser.throwError("Expected number in array declaration!");
            }

            token = parser.getToken(false);
            if (token.token != L"]") {
                parser.throwError("Expected ] character");
            }
        }
    }

    // Variable name
    token = parser.getToken(false);
    name = token.token;

    if (!isFunctionArgument) {
        // Function arguments can't have default values TODO

        token = parser.peekToken(false);

        if (token.token == L"=") {
            parser.eatToken(); // Remove previously peeked token

            // Directly initalize
            token = parser.getToken();


        }
    }

    string errorMessage;
    if (validateVariable(errorMessage)) {
        parser.throwError(errorMessage);
    }
}

bool Variable::validateVariable(std::string& result) {
    if (isArray && arrayLength == 0) {
        result = "Array length can't be 0";
        return true;
    }

    return false;
}
