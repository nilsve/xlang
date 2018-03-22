//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_SCOPE_H
#define XLANG_SCOPE_H


#include "../../utils/non_copyable.h"
#include "../TokenParser.h"
#include "Variable.h"
#include "instructions/Instruction.h"

#include <vector>
#include <memory>

class Scope : public non_copyable {
private:
    std::vector<std::shared_ptr<Scope>> scopes;
    std::vector<std::shared_ptr<Variable>> variables;
    std::vector<std::shared_ptr<Instruction>> instructions;

    std::unique_ptr<Scope> parseNestedScope(TokenParser& parser);
public:
    void Parse(TokenParser& parser);
};


#endif //XLANG_SCOPE_H
