//
// Created by Nils van Eijk on 02-03-18.
//

#ifndef XLANG_FUNCTION_H
#define XLANG_FUNCTION_H


#include "../TokenParser.h"
#include "Variable.h"

class Function : public non_copyable  {
private:
    std::wstring functionName;

    Variable returnVariable;
public:
    void Parse(TokenParser& parser);
};


#endif //XLANG_FUNCTION_H
