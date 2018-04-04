//
// Created by Nils van Eijk on 22-03-18.
//

#include "Scope.h"
#include "../compiler/instructions/CallInstruction.h"
#include "Function.h"
#include "Module.h"
#include "Data.h"
#include "../compiler/instructions/AssignInstruction.h"
#include "../compiler/StrongTarget.h"
#include "../compiler/WeakTarget.h"
#include "../compiler/Target.h"

#include <cassert>
#include <iostream>

using namespace std;

void Scope::Parse(TokenParser &parser) {
    assert(parser.getToken() == L"{");

    while(true) {
        auto token = parser.peekToken();

        if (token == L"{") {
            auto scope = parseNestedScope(parser);

            auto call = unique_ptr<Instruction>((Instruction*)(new CallInstruction(unique_ptr<Target>(new StrongTarget(*scope)))));
            instructions.emplace_back(std::move(call));

            scopes.push_back(std::move(scope));
        } else if (token == L"}") {
            parser.eatToken();
            break;
        } else if (Variable::isVariableType(token)) {
            declareVariable(parser);
        } else if (auto variable = getVariable(token)) {
            parser.eatToken();
            updateVariable(parser, *variable);
        } else {
            // Function call
            parseFunctionCall(parser);
        }
    }

    // TODO: Return?
}

void Scope::parseFunctionCall(TokenParser& parser) {
    auto token = parser.getToken();

    vector<const Variable*> arguments;
    wstring moduleName;
    wstring functionName = token.token;

    token = parser.getToken();

    if (token == L".") {
        // Function name isn't function name but module name
        moduleName = std::move(functionName);
        token = parser.getToken();
        functionName = token.token;
        token = parser.getToken();
    } else {
        moduleName = this->getParentFunction()->getParent()->getModuleName();
    }

    if (token != L"(") {
        parser.throwError("Expected ( after functionname");
    }

    token = parser.getToken();

    bool firstToken = true;
    while(token != L")") {
        // Handle arguments

        const Variable* argument = nullptr;
        if (!(argument = getVariable(token))) {
            return parser.throwError(L"Unknown variable " + token.token);
        }

        arguments.push_back(argument);

        token = parser.getToken();

        if (!firstToken) {
            // comma expected
            if (token != L",") {
                parser.throwError("Comma expected");
            }

            token = parser.getToken();

        }
        firstToken = false;
    }

    if (parser.getToken() != L";") {
        parser.throwError("Expected ; after function call!");
    }

    auto call = unique_ptr<Instruction>((Instruction*)(new CallInstruction(unique_ptr<Target>((Target*)(new WeakTarget(moduleName, functionName))), std::move(arguments))));

    instructions.emplace_back(std::move(call));
}

const vector<unique_ptr<Instruction>> &Scope::getInstructions() const {
    return instructions;
}

const Variable* Scope::getVariable(const Token& token) const {
    for (auto& variable : variables) {
        if (token == variable->getVariableName()) {
            return variable.get();
        }
    }

    if (auto scope = getParentScope()) {
        return scope->getVariable(token);
    }

    return nullptr;
}

std::unique_ptr<Scope> Scope::parseNestedScope(TokenParser &parser) {
    auto result = make_unique<Scope>(getParentFunction(), this);
    result->Parse(parser);
    return result;
}

const wstring &Scope::getScopeId() const {
    return scopeId;
}

const Function *Scope::getParentFunction() const {
    return parentFunction;
}

const Scope *Scope::getParentScope() const {
    return parentScope;
}

const vector<unique_ptr<Scope>> &Scope::getScopes() const {
    return scopes;
}

void Scope::updateVariable(TokenParser &parser, const Variable& variable) {
    assert(parser.getToken() == L"=");

    auto token = parser.getToken(true);

    const Data* _data = nullptr;

    if (token.isStringLiteral) {
        _data = &upsertData(token.token);
    } else {
        assert(false); // Not implemented!
    }

    instructions.push_back(std::make_unique<AssignInstruction>(variable, *_data));

    if (parser.getToken() != L";") {
        parser.throwError("Expected ;");
    }
}

void Scope::declareVariable(TokenParser &parser) {
    auto variable = make_unique<Variable>();
    variable->Parse(parser);
    variable->setVariableIndex(calculateVariableIndex());
    variables.push_back(std::move(variable));

    auto& _var = variables.back();
    auto token = parser.peekToken();
    if (token == L"=") {
        // Update variable
        updateVariable(parser, *_var);
    } else if (token != L";") {
        parser.throwError("Unexpected token after variable declaration!");
    } else {
        parser.eatToken();
    }
}

const vector<unique_ptr<Variable>> &Scope::getVariables() const {
    return variables;
}

template<typename T>
const Data& Scope::upsertData(T search) {
    for (auto& d : data) {
        if (*d == search) {
            return *d;
        }
    }

    auto d = make_unique<Data>();
    *d = search;

    data.push_back(std::move(d));

    return *data.back();
}

unsigned int Scope::calculateVariableIndex() const {
    unsigned int index = variables.size();

    if (auto parent = getParentScope()) {
        index += parent->calculateVariableIndex();
    }

    return index;
}
