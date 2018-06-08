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
#include "Container.h"

#include <vector>
#include <memory>

namespace xlang {
    namespace interpreter {

        class Function;

        class Scope : public Container, public utils::non_copyable {
        private:
            const bool isRawBlock = false;
            std::wstring rawCode;

            std::vector<std::unique_ptr<Scope>> scopes;

            void parseNestedScope(TokenParser &parser, bool isRawBlock = false);

            unsigned int calculateVariableIndex() const override;
        public:
            Scope(const Container *_parent, bool _isAsmBlock = false) : Container(utils::Utils::generateUuid(), _parent), isRawBlock(_isAsmBlock) {}

            void Parse(TokenParser &parser) override;

            const std::vector<std::unique_ptr<Scope>> &getScopes() const;

            const Variable *getVariable(const std::wstring& name) const override;

            const Function* getParentFunction() const;

            bool getIsRawBlock() const;

            const std::wstring &getRawCode() const;
        };
    }
}

#endif //XLANG_SCOPE_H
