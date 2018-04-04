//
// Created by Nils van Eijk on 08-03-18.
//

#ifndef XLANG_VARIABLE_H
#define XLANG_VARIABLE_H


#include "../../utils/non_copyable.h"
#include "../TokenParser.h"
#include <string>

class Scope;

class Variable : public non_copyable {
private:
    std::wstring dataType;
    const bool isFunctionArgument;
    std::wstring variableName;

    int variableIndex = -1; // Variable index (offset) on scope / module

    bool isPointer = false;
    bool isArray = false;
    size_t arrayLength = 0;

    bool validateVariable(std::string& result);
public:
    explicit Variable(bool isFunctionArgument = false) : isFunctionArgument(isFunctionArgument) {}

    void Parse(TokenParser& parser);

    static bool isVariableType(const Token& token);

    static std::unique_ptr<Variable> parseFunctionArg(TokenParser &parser);

    const std::wstring &getVariableName() const;

    void setVariableIndex(int variableIndex);
    int getVariableIndex() const;

    const std::wstring &getDataType() const;
};


#endif //XLANG_VARIABLE_H
