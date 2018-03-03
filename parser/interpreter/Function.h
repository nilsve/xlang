//
// Created by Nils van Eijk on 02-03-18.
//

#ifndef XLANG_FUNCTION_H
#define XLANG_FUNCTION_H


#include "../TokenParser.h"

class Function {
private:
    std::wstring functionName;
public:
    Function(const std::wstring& functionName) : functionName(functionName) {}
    void Parse(TokenParser& parser);
};


#endif //XLANG_FUNCTION_H
