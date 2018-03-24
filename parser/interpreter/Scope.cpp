//
// Created by Nils van Eijk on 22-03-18.
//

#include "Scope.h"
#include "instructions/CallInstruction.h"

#include <string>

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

        } else if (isVariable(token)) {

        } else {
            // Function call
            std::vector<std::weak_ptr<Variable>> arguments;
            wstring moduleName, functionName;
            functionName = token.token;

            token = parser.getToken(false);

            if (token == L".") {
                // Function name isn't function name but module name
                moduleName = functionName;
                token = parser.getToken(false);
                functionName = token.token;
            }

            if (token != L"(") {
                parser.throwError("Expected ( after functionname");
            }

            token = parser.getToken(false);

            bool firstToken = true;
            while(token != L")") {
                // Handle arguments

                weak_ptr<Variable> argument;
                if (!getVariable(token, argument)) {
                    parser.throwError(L"Unknown variable " + token.token);
                }

                arguments.push_back(std::move(argument));

                token = parser.getToken(false);

                if (!firstToken) {
                    // comma expected
                    if (token != L",") {
                        parser.throwError("Comma expected");
                    }

                    token = parser.getToken(false);

                }
                firstToken = false;
            }

            if (parser.getToken(false) != L";") {
                parser.throwError("Expected ; after function call!");
            }

            auto call = unique_ptr<Instruction>((Instruction*)(new CallInstruction(functionName, std::move(arguments))));

            instructions.emplace_back(std::move(call));
        }
    }

    // TODO: Return?
}

bool Scope::getVariable(const Token& token, weak_ptr<Variable>& variable) {
    for (auto& _variable : variables) {
        if (token == _variable->getVariableName()) {
            variable = _variable;
            return true;
        }
    }

    return false;
}

bool Scope::isVariable(const Token& token) {
    weak_ptr<Variable> _var;
    return getVariable(token, _var);
}

std::unique_ptr<Scope> Scope::parseNestedScope(TokenParser &parser) {
    auto result = make_unique<Scope>();
    result->Parse(parser);
    return result;
}
