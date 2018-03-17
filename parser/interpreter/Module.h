//
// Created by Nils van Eijk on 02-03-18.
//

#ifndef XLANG_MODULE_H
#define XLANG_MODULE_H

#include <string>
#include "../TokenParser.h"
#include "Function.h"
#include "Variable.h"
#include <vector>

class Module : public non_copyable  {
private:
    std::wstring moduleName;
    std::vector<std::shared_ptr<Function>> functions;
    std::vector<std::shared_ptr<Variable>> variables;

    void parseFunction(TokenParser &parser);
    void parseVariable(TokenParser &parser, const Token& dataType);
public:
    void Parse(TokenParser& parser);

};


#endif //XLANG_MODULE_H
