//
// Created by Nils van Eijk on 07-05-18.
//

#ifndef XLANG_CONTAINER_H
#define XLANG_CONTAINER_H


#include <string>
#include "TokenParser.h"
#include "Variable.h"
#include "Data.h"
#include "../compiler/instructions/Instruction.h"

namespace xlang {
    namespace interpreter {
        class Container {
        protected:
            std::wstring id;
            const Container* parent;
            std::vector<std::unique_ptr<Data>> data;
            std::vector<std::unique_ptr<Variable>> variables;
            std::vector<std::unique_ptr<compiler::instructions::Instruction>> instructions;

            const Data &upsertData(const Token& search);

        public:
            Container() {}
            Container(const std::wstring& _id, const Container *_parent) : id(_id), parent(_parent) {}
            virtual void Parse(TokenParser &parser) = 0;
            const std::wstring &getId() const;

            const Container *getParent() const;
            virtual unsigned int calculateVariableIndex() const {
                return 0;
            };

            const std::vector<std::unique_ptr<Variable>> &getVariables() const;

            const Variable *getVariable(const Token &token) const {
                return getVariable(token.token);
            }

            Variable& createVariable(bool isFunctionArgument) {
                auto index = calculateVariableIndex();
                variables.push_back(std::make_unique<Variable>(isFunctionArgument));
                auto& variable = variables.back();
                variable->setVariableIndex(index);
                return *variable;
            }

            virtual const Variable *getVariable(const std::wstring& name) const;

            void parseArithmeticBlock(std::vector<const Token>::iterator& startToken, std::vector<const Token>::iterator& endToken, const Variable &targetVariable, bool isRootBlock);

            void assignVariable(TokenParser &parser, const Variable &targetVariable);

            void declareVariable(TokenParser &parser);

            const std::vector<std::unique_ptr<Data>> &getData() const;

            const std::vector<std::unique_ptr<compiler::instructions::Instruction>> &getInstructions() const;

            void parseFunctionCall(TokenParser &parser);
        };
    }
}




#endif //XLANG_CONTAINER_H
