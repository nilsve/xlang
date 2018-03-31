//
// Created by Nils van Eijk on 08-03-18.
//

#include "Variable.h"

#include <set>
#include <string>
#include <sstream>

using namespace std;

bool Variable::isVariableType(const Token& token) {
    static set<wstring> dataTypes = {
        L"char",
        L"int"
    };

    return dataTypes.find(token.token) != dataTypes.end();
}

void Variable::Parse(TokenParser &parser) {
    auto token = parser.getToken();
    dataType = token.token;
    token = parser.getToken();

    if (token == L"[" || token == L"*") {
        switch (token.token[0]) {
            case L'[':
                //FIXME: No array support yet.
                parser.throwError("No array support!");

                if (isFunctionArgument) {
                    parser.throwError("Function argument can't be an array!");
                }

                isArray = true;

                token = parser.getToken();

                if (token == L"]") {
                    // Array of yet unknown length
                } else {

                    if (isFunctionArgument) {
                        parser.throwError(L"Function argument of type array can't have fixed size!");
                    }

                    std::wstringstream ss(token.token);
                    if ((ss >> arrayLength).fail() || !(ss >> std::ws).eof()) {
                        return parser.throwError("Expected number in array declaration!");
                    }

                    token = parser.getToken();
                    if (token != L"]") {
                        parser.throwError("Expected ] character");
                    }
                }
                break;
            case L'*':
                isPointer = true;
                break;
        }

        // Variable name
        token = parser.getToken();
    }

    variableName = token.token;

    /*if (!isFunctionArgument) {
        // Function arguments can't have default values TODO

        token = parser.peekToken(false);

        if (token == L"=") {
            parser.eatToken(); // Remove previously peeked token

            // Directly initialize
            token = parser.getToken();

            //FIXME
        }
    }*/

    string errorMessage;
    if (validateVariable(errorMessage)) {
        parser.throwError(errorMessage);
    }
}

const wstring &Variable::getVariableName() const {
    return variableName;
}

bool Variable::validateVariable(std::string& result) {
    if (isArray && arrayLength == 0) {
        result = "Array length can't be 0";
        return true;
    }

    return false;
}

std::unique_ptr<Variable> Variable::parseFunctionArg(TokenParser &parser) {
    auto result = make_unique<Variable>(true);
    result->Parse(parser);
    return result;
}
