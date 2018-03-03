//
// Created by Nils van Eijk on 02-03-18.
//

#ifndef XLANG_MODULE_H
#define XLANG_MODULE_H

#include <string>
#include "../TokenParser.h"

class Module {
private:
    std::wstring moduleName;

    void parseFunction(TokenParser &parser);
public:
    void Parse(TokenParser& parser);
};


#endif //XLANG_MODULE_H
