//
// Created by Nils van Eijk on 07-05-18.
//

#include <memory>
#include "Container.h"
#include "../compiler/instructions/AssignInstruction.h"
#include "../../utils/Utils.h"
#include <string>

namespace xlang {
    namespace interpreter {
        using namespace std;
        using namespace compiler::instructions;

        const std::wstring &Container::getId() const {
            return id;
        }

        const Container *Container::getParent() const {
            return parent;
        }

        const Variable *Container::getVariable(const std::wstring& name) const {

            for (auto &variable : getVariables()) {
                if (name == variable->getVariableName()) {
                    return variable.get();
                }
            }

            if (auto parent = getParent()) {
                return parent->getVariable(name);
            }

            return nullptr;
        }

        const std::vector<std::unique_ptr<Variable>> &Container::getVariables() const {
            return variables;
        }

        void Container::parseArithmeticBlock(TokenParser& parser, const Variable& targetVariable, bool isRootBlock = true) {

            auto token = parser.getToken(true);

            if (token == L"(") {
                auto& variable = variables.emplace_back(new Variable());
                parseArithmeticBlock(parser, *variable, false);
                auto assignInstruction = unique_ptr<Instruction>((Instruction * )(new AssignInstruction(targetVariable, *variable)));
                instructions.push_back(std::move(assignInstruction));
            } else {
                do {
                    if (token.isStringLiteral) {
                        if (auto sourceVariable = getVariable(token)) {
                            instructions.push_back(std::make_unique<AssignInstruction>(targetVariable, *sourceVariable));
                        } else {
                            instructions.push_back(std::make_unique<AssignInstruction>(targetVariable, upsertData(token.token)));
                        }
                    } else if (utils::Utils::isNumber(token.token)) {
                        // Number
                        auto constSimpleData = make_unique<Variable>();
                        constSimpleData->markTemporary();
                        constSimpleData->setDataType(targetVariable.getDataType());
                        constSimpleData->setModifierType(targetVariable.getModifierType());
                        constSimpleData->constSimpleData = token.token;
                        instructions.push_back(std::make_unique<AssignInstruction>(targetVariable, std::move(constSimpleData)));
                    } else {

                    }

                    token = parser.getToken(true);

                } while (!(token == L")" || (isRootBlock && token == L";")));
            }
        }

        void Container::assignVariable(TokenParser &parser, const Variable& targetVariable) {

            auto token = parser.getToken(false);

            if (token == L".") {
                // Possibly accidentally declared variable with same name as module name
                parser.throwError(L"Trying to access functions on variable!");
            }

            assert(token == L"=");

            parseArithmeticBlock(parser, targetVariable);
        }

        void Container::declareVariable(TokenParser &parser) {
            auto _variable = make_unique<Variable>();

            _variable->Parse(parser);

            if (getVariable(_variable->getVariableName())) {
                parser.throwError(L"Attempt to redeclare variable \"" + _variable->getVariableName() + L"\"");
            }

            _variable->setVariableIndex(calculateVariableIndex());
            variables.push_back(std::move(_variable));
            auto& variable = variables.back();
            auto token = parser.peekToken();
            if (token == L"=") {
                // Update variable
                assignVariable(parser, *variable);
            } else if (token != L";") {
                parser.throwError(L"Unexpected token after variable declaration!");
            } else {
                parser.eatToken();
            }
        }

        template<typename T>
        const Data &Container::upsertData(T search) {
            for (auto &d : data) {
                if (*d == search) {
                    return *d;
                }
            }

            auto d = make_unique<Data>();
            *d = search;

            data.push_back(std::move(d));

            return *data.back();
        }
    }
}

