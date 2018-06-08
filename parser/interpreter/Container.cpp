//
// Created by Nils van Eijk on 07-05-18.
//

#include <memory>
#include "Container.h"
#include "Module.h"
#include "../compiler/instructions/CallInstruction.h"
#include "../compiler/instructions/AssignInstruction.h"
#include "../compiler/StrongTarget.h"
#include "../compiler/WeakTarget.h"
#include "../compiler/Target.h"
#include "../../utils/Utils.h"
#include "VariableLink.h"

#include <string>
#include <set>

namespace xlang {
    namespace interpreter {
        using namespace std;
        using namespace compiler::instructions;
        using namespace compiler;

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

        void Container::parseFunctionCall(TokenParser &parser) {
            auto token = parser.getToken();

            vector<VariableLink> arguments;
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

                const Module* module = nullptr;
                const Container* currentContainer = dynamic_cast<const Container*>(this);

                while (true) {
                    module = dynamic_cast<const Module*>(currentContainer);

                    if (module) {
                        moduleName = module->getId();
                        break;
                    } else {
                        currentContainer = currentContainer->getParent();
                        if (!currentContainer) {
                            parser.throwError(L"Parent module not found!");
                        }
                    }
                }

            }

            if (token != L"(") {
                parser.throwError(L"Expected ( after functionname");
            }

            token = parser.peekToken(true);

            while (token != L")") {
                auto& variable = createVariable(true);

                auto tokens = parser.getTokens({L",", L")"});

                if (!tokens.size()) {
                    parser.throwError(L"Empty argument");
                }

                auto start = tokens.begin();
                auto end = tokens.end();

                parseArithmeticBlock(start, end, variable, true);

                arguments.push_back({variable, false});

                token = parser.peekToken(true);
            }

            parser.eatToken();

            if (parser.getToken() != L";") {
                parser.throwError(L"Expected ; after function call!");
            }

            auto call = unique_ptr<Instruction>((Instruction * )(new CallInstruction(
                    unique_ptr<Target>((Target * )(new WeakTarget(moduleName, functionName))), std::move(arguments))));

            instructions.push_back(std::move(call));
        }

        const std::vector<std::unique_ptr<Variable>> &Container::getVariables() const {
            return variables;
        }

        void Container::parseArithmeticBlock(std::vector<const Token>::iterator& startToken, std::vector<const Token>::iterator& endToken, const Variable& targetVariable, bool isRootBlock = true) {

            // Start out with assign
            ArithmeticType type = ArithmeticType::ASSIGN;

            // Parse all tokens
            while (startToken != endToken) {
                auto token = *startToken;
                unique_ptr<AssignInstruction> assignInstruction;

                const Variable* var = nullptr;
                const Data* data = nullptr;

                if (token == L"(") {
                    startToken++;
                    var = &createVariable(false);
                    parseArithmeticBlock(startToken, endToken, *var, false);
                } else {
                    if (!utils::Utils::isNumber(token.token)) {
                        if (token.isStringLiteral) {
                            data = &upsertData(token);
                        } else {
                            if (auto sourceVariable = getVariable(token)) {
                                var = sourceVariable;
                            } else {
                                //FIXME
                                assert(false);
//                                    parser.throwError(L"Unknown variable " + std::wstring(token.token));
                            }
                        }
                    } else {
                        data = &upsertData(token);
                    }
                }

                if (data) {
                    assignInstruction = std::make_unique<AssignInstruction>(targetVariable, *data);
                } else if (var) {
                    assignInstruction = std::make_unique<AssignInstruction>(targetVariable, *var);
                } else {
                    assert(false);
                }

                assignInstruction->setArithmeticOperation(type);
                instructions.push_back(std::move(assignInstruction));

                startToken++;

                if (startToken != endToken) {
                    token = *startToken;

                    if (token == L"+") {
                        type = ArithmeticType::ADD;
                    } else if (token == L"-") {
                        type = ArithmeticType::SUBSTRACT;
                    } else if (token == L"*") {
                        type = ArithmeticType::MULTIPLY;
                    } else if (token == L"/") {
                        type = ArithmeticType::DIVIDE;
                    } else if (!isRootBlock && token == L")") {
                        return;
                    } else {
                        // FIXME: Moet een exception zijn
                        assert(false);
                    }

                    startToken++;
                }
            }
        }

        void Container::assignVariable(TokenParser &parser, const Variable& targetVariable) {

            auto token = parser.getToken(false);

            if (token == L".") {
                // Possibly accidentally declared variable with same name as module name
                parser.throwError(L"Trying to access functions on variable!");
            }

            assert(token == L"=");

            auto tokens = parser.getTokens({L";"});
            parser.eatToken();

            auto start = tokens.begin();
            auto end = tokens.end();

            parseArithmeticBlock(start, end, targetVariable, true);
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

        const Data &Container::upsertData(const Token& token) {
            for (auto &d : data) {
                if (d->getIsNumber() == !token.isStringLiteral && *d == token.token) {
                    return *d;
                }
            }

            auto d = make_unique<Data>(!token.isStringLiteral);
            *d = token.token;

            data.push_back(std::move(d));

            return *data.back();
        }

        const vector<unique_ptr<Data>> &Container::getData() const {
            return data;
        }

        const vector<unique_ptr<Instruction>> &Container::getInstructions() const {
            return instructions;
        }
    }
}

