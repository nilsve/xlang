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
            static std::map<std::wstring, ModifierType> modifierTypes;
            static std::map<std::wstring, DataType> dataTypes;

            static DataType resolveDataType(const Token& token);
            static ModifierType resolveModifierType(const Token &token);

            const bool isFunctionArgument;
            std::wstring variableName;
            DataType dataType;
            ModifierType modifierType;
            bool isPointer = false;
            bool isArray = false;
            size_t arrayLength = 0;
            bool isTemporary = false;

            int variableIndex = -1; // Variable index (offset) on SCOPE / module


            bool validateVariable(std::wstring &result);
        public:
            explicit Variable(bool isFunctionArgument = false) : isFunctionArgument(isFunctionArgument) {}

            void markTemporary();

            void Parse(TokenParser &parser);

            ModifierType getModifierType() const;

            bool getIsPointer() const;

            static bool isVariableType(const Token &token);

            static std::unique_ptr<Variable> parseFunctionArg(TokenParser &parser);

            const std::wstring &getVariableName() const;
            void setVariableIndex(int variableIndex);

            void setDataType(DataType dataType);

            int getVariableIndex() const;
            DataType getDataType() const;

            bool supportsArithmeticOperator(const Token &token);

            bool getIsTemporary() const;

            void setModifierType(ModifierType modifierType);

            static void setModifierTypes(const std::map<std::wstring, ModifierType> &modifierTypes);
        };
    }
}

#endif //XLANG_VARIABLE_H
