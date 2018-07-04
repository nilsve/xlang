//
// Created by Nils van Eijk on 02-03-18.
//

#include "Function.h"

#include <cassert>

namespace xlang {
    namespace interpreter {

        using namespace std;

        void Function::Parse(TokenParser &parser) {
            parseHeader(parser);
            parseBody(parser);
        }

        void Function::parseHeader(TokenParser &parser) {
            parser.debugAssertNext(L"function");

            auto functionName = parser.getToken();
            this->id = functionName.token;

            auto token = parser.getToken();

            if (token != L"(") {
                CallingConvention convention = getCallingConvention(token.token);
                if (convention != CallingConvention::UNKNOWN) {
                    callingConvention = convention;
                } else {
                    parser.throwError(L"Unexpected token after function name!");
                }

                token = parser.getToken();
            }

            if (token != L"(") {
                parser.throwError(L"Expected (");
            }

            if (parser.peekToken(false) != L")") {
                while (token != L")") {
                    // Handle parameters

                    auto parameter = Variable::parseFunctionArg(parser);
                    parameter->setVariableIndex((parameters.size() + 1) * -1);
                    parameters.push_back(std::move(parameter));

                    token = parser.getToken();

                    // comma expected
                    if (token != L",") {
                        break;
                    }

                }
            } else {
                parser.eatToken();
            }

            token = parser.peekToken();

            if (token == L":") {
                // Return type
                parser.eatToken();
                token = parser.getToken();
            }
        }

        void Function::parseBody(TokenParser &parser) {
            rootScope = make_unique<Scope>(this);
            rootScope->Parse(parser);
        }

        CallingConvention Function::getCallingConvention(const std::wstring &convention) {
            if (convention == L"cdecl") {
                return CallingConvention::CDECL;
            } else if (convention == L"stdcall") {
                return CallingConvention::STDCALL;
            } else {
                return CallingConvention::UNKNOWN;
            }
        }

        CallingConvention Function::getCallingConvention() const {
            return callingConvention;
        }

        const vector<unique_ptr<Variable>> &Function::getParameters() const {
            return parameters;
        }

        const unique_ptr<Variable> &Function::getReturnVariable() const {
            return returnVariable;
        }

        const unique_ptr<Scope> &Function::getRootScope() const {
            return rootScope;
        }
    }
}