//
// Created by Nils van Eijk on 02-03-18.
//

#include "Function.h"

using namespace std;

void Function::Parse(TokenParser &parser) {
    parseHeader(parser);
    parseBody(parser);
}

void Function::parseHeader(TokenParser& parser) {
    auto functionName = parser.getToken(false);
    this->functionName = functionName.token;

    auto token = parser.getToken(false);

    if (token != L"(") {
        CallingConvention convention = getCallingConvention(token.token);
        if (convention != CallingConvention::unknown) {
            callingConvention = convention;
        } else {
            parser.throwError("Unexpected token after function name!");
        }
    }

    token = parser.getToken(false);

    if (token != L"(") {
        parser.throwError("Expected (");
    }

    bool firstToken = true;
    while(token != L")") {
        // Handle parameters

        auto parameter = Variable::parseFunctionArg(parser);
        parameters.push_back(std::move(parameter));

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

    token = parser.getToken(false);

    if (token == L":") {
        // Return type
        token = parser.getToken(false);
    }
}

void Function::parseBody(TokenParser& parser) {
    rootScope = make_shared<Scope>();
    rootScope->Parse(parser);
}

CallingConvention Function::getCallingConvention(const std::wstring &convention) {
    if (convention == L"cdecl") {
        return CallingConvention::cdecl;
    } else if (convention == L"stdcall") {
        return CallingConvention::stdcall;
    } else {
        return CallingConvention::unknown;
    }
}

const wstring &Function::getFunctionName() const {
    return functionName;
}

CallingConvention Function::getCallingConvention() const {
    return callingConvention;
}

const vector<shared_ptr<Variable>> &Function::getParameters() const {
    return parameters;
}

const unique_ptr<Variable> &Function::getReturnVariable() const {
    return returnVariable;
}

const shared_ptr<Scope> &Function::getRootScope() const {
    return rootScope;
}