//
// Created by Nils van Eijk on 22-03-18.
//

#include "Scope.h"
#include "Function.h"
#include "Module.h"
#include "Data.h"
#include "Variable.h"
#include "../compiler/instructions/CallInstruction.h"
#include "../compiler/Target.h"
#include "../compiler/StrongTarget.h"
#include <cassert>
#include <iostream>

namespace xlang {
    namespace interpreter {

        using namespace std;
        using namespace compiler;
        using namespace compiler::instructions;
        using namespace utils;

        void Scope::Parse(TokenParser &parser) {
            parser.debugAssertNext(L"{");

            if (getIsRawBlock()) {
                rawCode = parser.readUntill(L'}');
            }

            while (true) {
                auto token = parser.peekToken();

                if (token == L"{") {
                    parseNestedScope(parser);
                } else if (token == L"}") {
                    parser.eatToken();
                    break;
                } else if (token == L"__raw") {
                    parser.eatToken();
                    parseNestedScope(parser, true);
                } else if (Variable::isVariableType(token)) {
                    declareVariable(parser);
                } else if (auto variable = Container::getVariable(token)) {
                    parser.eatToken();
                    assignVariable(parser, *variable);
                } else {
                    // Function call
                    parseFunctionCall(parser);
                }
            }

            // TODO: Return?
        }

        bool Scope::getIsRawBlock() const {
            return isRawBlock;
        }

        const Variable *Scope::getVariable(const std::wstring& name) const {
            // FIXME: Deze call is recursief. De arguments worden dus voor iedere geneste scope nog een keer uitgelezen
            if (auto parentFunction = getParentFunction()) {
                for (auto &argument : parentFunction->getParameters()) {
                    if (name == argument->getVariableName()) {
                        return argument.get();
                    }
                }
            }

            return Container::getVariable(name);
        }

        void Scope::parseNestedScope(TokenParser &parser, bool isRawBlock) {
            auto scope = make_unique<Scope>(this, isRawBlock);
            scope->Parse(parser);

            auto call = unique_ptr<Instruction>(
                    (Instruction * )(new CallInstruction(unique_ptr<Target>(new StrongTarget(*scope)))));
            instructions.push_back(std::move(call));

            scopes.push_back(std::move(scope));
        }

        const vector<unique_ptr<Scope>> &Scope::getScopes() const {
            return scopes;
        }

        unsigned int Scope::calculateVariableIndex() const {
            unsigned int index = variables.size();

            if (auto parent = dynamic_cast<const Scope*>(getParent())) {
                index += parent->calculateVariableIndex();
            }

            return index;
        }

        const wstring &Scope::getRawCode() const {
            return rawCode;
        }

        const Function *Scope::getParentFunction() const {
            if (auto parent = dynamic_cast<const Function*>(getParent())) {
                return parent;
            } else if (auto scope = dynamic_cast<const Scope*>(getParent())) {
                return scope->getParentFunction();
            } else {
                assert(false);
            }
        }
    }
}