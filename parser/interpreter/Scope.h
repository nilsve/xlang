//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_SCOPE_H
#define XLANG_SCOPE_H


#include "../../utils/non_copyable.h"
#include "../TokenParser.h"
#include "Variable.h"
#include "../compiler/instructions/Instruction.h"
#include "../../utils/Utils.h"

#include <vector>
#include <memory>

class Function;

class Scope : public non_copyable {
private:
    const std::wstring scopeId;
    const Function* parentFunction = nullptr;
    const Scope* parentScope = nullptr;

    std::vector<std::unique_ptr<Scope>> scopes;
    std::vector<std::unique_ptr<Variable>> variables;
    std::vector<std::unique_ptr<Instruction>> instructions;
    std::vector<std::unique_ptr<std::wstring>> stringConstants;

    std::unique_ptr<Scope> parseNestedScope(TokenParser& parser);
    void parseFunctionCall(TokenParser& parser);
    void parseVariableDeclaration(TokenParser& parser);
    void updateVariable(TokenParser &parser, Variable& variable);

    bool isVariable(const Token& token) const;

    const Variable* getVariable(const Token &token) const;
public:
    Scope(const Function* _parentFunction, const Scope* _parentScope) : scopeId(Utils::generateUuid()), parentFunction(_parentFunction), parentScope(_parentScope) {}
    void Parse(TokenParser& parser);

    const std::vector<std::unique_ptr<Instruction>> &getInstructions() const;

    const std::wstring &getScopeId() const;
    const Function *getParentFunction() const;
    const Scope *getParentScope() const;
    const std::vector<std::unique_ptr<Scope>> &getScopes() const;
};


#endif //XLANG_SCOPE_H
