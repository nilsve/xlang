//
// Created by Nils van Eijk on 20-02-18.
//

#ifndef XLANG_CODEFILE_H
#define XLANG_CODEFILE_H


#include <string>
#include "../../utils/non_copyable.h"

namespace xlang {
    namespace interpreter {

        class Parser;

        class CodeFile : public utils::non_copyable {
        private:
            Parser &parser;
            const std::wstring relativePath;
            std::wstring code;

            void resolveImports();

            std::wstring resolvePath(std::wstring relativePath);

        public:
            CodeFile(std::wstring relativePath, Parser &parser);

            const std::wstring &getCode() const;

            void Load();
        };
    }
}

#endif //XLANG_CODEFILE_H
