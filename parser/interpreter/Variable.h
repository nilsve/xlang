//
// Created by Nils van Eijk on 08-03-18.
//

#ifndef XLANG_VARIABLE_H
#define XLANG_VARIABLE_H


#include "../../utils/non_copyable.h"
#include "TokenParser.h"
#include <string>
#include <map>

namespace xlang {
    namespace interpreter {

        enum class ModifierType {
            UNKNOWN,
            UNSIGNED,
            SIGNED,
        };

        enum class DataType {
            UNKNOWN,
            CHAR,
            INT,
            FLOAT,
            DOUBLE,
        };

        class Scope;

        class Variable : public utils::non_copyable {
        private:
            const bool isFunctionArgument;
            std::wstring variableName;
            DataType dataType;
            ModifierType modifierType;
            bool isPointer = false;
            bool isArray = false;
            size_t arrayLength = 0;

            int variableIndex = -1; // Variable index (offset) on SCOPE / module


            bool validateVariable(std::string &result);

            static std::map<std::wstring, ModifierType> modifierTypes;
        public:
            DataType getDataType() const;

        private:
            static std::map<std::wstring, DataType> dataTypes;

            static DataType resolveDataType(const Token& token);
            static ModifierType resolveModifierType(const Token &token);

        public:
            explicit Variable(bool isFunctionArgument = false) : isFunctionArgument(isFunctionArgument) {}

            void Parse(TokenParser &parser);

            static bool isVariableType(const Token &token);

            static std::unique_ptr<Variable> parseFunctionArg(TokenParser &parser);

            const std::wstring &getVariableName() const;

            void setVariableIndex(int variableIndex);

            int getVariableIndex() const;
        };
    }
}

#endif //XLANG_VARIABLE_H
