//
// Created by Nils van Eijk on 08-03-18.
//

#ifndef XLANG_VARIABLE_H
#define XLANG_VARIABLE_H


#include "../../utils/non_copyable.h"
#include "../TokenParser.h"
#include <string>

class Variable : public non_copyable {
private:
    const std::wstring dataType;
    const bool isFunctionArgument;
    std::wstring name;

    bool isPointer = false;
    bool isArray = false;
    size_t arrayLength = 0;

    bool validateVariable(std::string& result);
public:
    Variable(const std::wstring& dataType, bool isFunctionArgument) : dataType(dataType), isFunctionArgument(isFunctionArgument) {}

    void Parse(TokenParser& parser);

    static bool isVariableType(const std::wstring& token);
};


#endif //XLANG_VARIABLE_H
