//
// Created by Nils van Eijk on 08-03-18.
//

#include "Variable.h"

#include <map>
#include <string>
#include <sstream>

namespace xlang {
    namespace interpreter {

        using namespace std;

        map<wstring, ModifierType> Variable::modifierTypes = {
                {L"unsigned", ModifierType::UNSIGNED},
                {L"signed", ModifierType::SIGNED},
        };

        map<wstring, DataType> Variable::dataTypes = {
                {L"int", DataType::INT},
                {L"char", DataType::CHAR},
                {L"double", DataType::DOUBLE},
                {L"float", DataType::FLOAT},
        };

        bool Variable::isVariableType(const Token &token) {
            return resolveDataType(token) != DataType::UNKNOWN || resolveModifierType(token) != ModifierType::UNKNOWN;
        }

        void Variable::Parse(TokenParser &parser) {
            auto token = parser.getToken();

            auto modifierType = resolveModifierType(token);
            if (modifierType != ModifierType::UNKNOWN) {

            }

            dataType = resolveDataType(token);

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
                            // Array of yet UNKNOWN length
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

            string errorMessage;
            if (validateVariable(errorMessage)) {
                parser.throwError(errorMessage);
            }
        }

        const wstring &Variable::getVariableName() const {
            return variableName;
        }

        bool Variable::validateVariable(std::string &result) {
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

        void Variable::setVariableIndex(int variableIndex) {
            Variable::variableIndex = variableIndex;
        }

        int Variable::getVariableIndex() const {
            return variableIndex;
        }

        ModifierType Variable::resolveModifierType(const Token &token) {
            if (modifierTypes.find(token.token) != modifierTypes.end()) {
                return modifierTypes[token.token];
            } else {
                return ModifierType::UNKNOWN;
            }
        }

        DataType Variable::resolveDataType(const Token &token) {
            if (dataTypes.find(token.token) != dataTypes.end()) {
                return dataTypes[token.token];
            } else {
                return DataType::UNKNOWN;
            }
        }

        DataType Variable::getDataType() const {
            return dataType;
        }

        bool Variable::supportsArithmeticOperator(const Token &token) {
            if (getIsPointer()) {
                return true;
            } else {
                switch (getDataType()) {
                    case DataType::DOUBLE:
                    case DataType::FLOAT:
                    case DataType::INT:
                    case DataType::CHAR:
                        if (token == L"+" || token == L"-" || token == L"*" || token == L"/") {
                            return true;
                        }
                        break;
                    case DataType::UNKNOWN:
                        assert(false);
                        break;
                    default:
                        return false;
                }
            }

            return false;
        }

        void Variable::setModifierType(ModifierType modifierType) {
            Variable::modifierType = modifierType;
        }

        bool Variable::getIsPointer() const {
            return isPointer;
        }

        void Variable::markTemporary() {
            isPointer = false;
            isTemporary = true;
        }

        bool Variable::getIsTemporary() const {
            return isTemporary;
        }

        void Variable::setDataType(DataType dataType) {
            Variable::dataType = dataType;
        }

        ModifierType Variable::getModifierType() const {
            return modifierType;
        }

        void Variable::setModifierTypes(const map<wstring, ModifierType> &modifierTypes) {
            Variable::modifierTypes = modifierTypes;
        }
    }
}