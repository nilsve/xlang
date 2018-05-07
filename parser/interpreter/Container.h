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

            template<typename T>
            const Data &upsertData(T search);

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

            const Variable *getVariable(const std::wstring& name) const;

            void parseArithmeticBlock(TokenParser &parser, const Variable &targetVariable, bool isRootBlock);

            void assignVariable(TokenParser &parser, const Variable &targetVariable);

            void declareVariable(TokenParser &parser);
        };
    }
}




#endif //XLANG_CONTAINER_H
