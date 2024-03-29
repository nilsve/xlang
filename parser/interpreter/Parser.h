//
// Created by Nils van Eijk on 20-02-18.
//

#ifndef XLANG_PARSER_H
#define XLANG_PARSER_H

#include <vector>
#include <string>
#include <memory>
#include "../../utils/non_copyable.h"
#include "CodeFile.h"
#include "TokenParser.h"
#include "Module.h"

namespace xlang {
    namespace interpreter {

        class Parser : public utils::non_copyable {
        private:
            bool parsed = false;

            const std::wstring workspace;

            std::vector<std::unique_ptr<CodeFile>> codeFiles;
            std::vector<std::unique_ptr<Module>> modules;

            CodeFile *mainFile;

            void parseModule(TokenParser &parser);

        public:
            Parser(const std::wstring &workspace, const std::wstring &mainFilePath);
            void Parse();
            CodeFile &loadFile(const std::wstring &filePath);

            const std::vector<std::unique_ptr<Module>> &getModules() const;

            const std::wstring &getWorkspace() const;
        };
    }
}

#endif //XLANG_PARSER_H
