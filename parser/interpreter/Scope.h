//
// Created by Nils van Eijk on 22-03-18.
//

#ifndef XLANG_SCOPE_H
#define XLANG_SCOPE_H


#include "../../utils/non_copyable.h"
#include "TokenParser.h"
#include "Variable.h"
#include "../compiler/instructions/Instruction.h"
#include "../../utils/Utils.h"
#include "Data.h"

#include <vector>
#include <memory>

namespace xlang {
    namespace interpreter {

        class Function;

        class Scope : public utils::non_copyable {
        private:
            const std::wstring scopeId;
            const Function *parentFunction = nullptr;
            const Scope *parentScope = nullptr;
            const bool isRawBlock = false;
            std::wstring rawCode;

            std::vector<std::unique_ptr<Scope>> scopes;
            std::vector<std::unique_ptr<Variable>> variables;
            std::vector<std::unique_ptr<compiler::instructions::Instruction>> instructions;
            std::vector<std::unique_ptr<Data>> data;

            void parseNestedScope(TokenParser &parser, bool isRawBlock = false);

            void parseFunctionCall(TokenParser &parser);

            void declareVariable(TokenParser &parser);

            void assignVariable(TokenParser &parser, const Variable &variable);

            const Variable *getVariable(const Token &token) const;

            unsigned int calculateVariableIndex() const;

        public:
            Scope(const Function *_parentFunction, const Scope *_parentScope, bool _isAsmBlock = false) : scopeId(utils::Utils::generateUuid()),
                                                                                parentFunction(_parentFunction),
                                                                                parentScope(_parentScope),
                                                                                isRawBlock(_isAsmBlock) {}

            void Parse(TokenParser &parser);

            const std::vector<std::unique_ptr<compiler::instructions::Instruction>> &getInstructions() const;

            const std::wstring &getScopeId() const;

            const Function *getParentFunction() const;

            const Scope *getParentScope() const;

            const std::vector<std::unique_ptr<Scope>> &getScopes() const;

            const std::vector<std::unique_ptr<Variable>> &getVariables() const;

            const std::vector<std::unique_ptr<Data>> &getData() const;

            template<typename T>
            const Data &upsertData(T search);

            bool getIsRawBlock() const;

            const std::wstring &getRawCode() const;

            const Variable &parseArithmeticOperations(TokenParser &parser, const Token& token);
        };
    }
}

#endif //XLANG_SCOPE_H
