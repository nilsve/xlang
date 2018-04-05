//
// Created by Nils van Eijk on 20-02-18.
//

#include "Parser.h"
#include "../../utils/Utils.h"
#include "TokenParser.h"
#include "Module.h"

#include <string>
#include <exception>
#include <cassert>

using namespace std;

namespace xlang {
    namespace interpreter {

        Parser::Parser(const std::wstring &workspace, const std::wstring &mainFilePath) : workspace(workspace) {
            auto &codeFile = loadFile(mainFilePath);
            mainFile = &codeFile;
            mainFile->Load();
        }

        void Parser::Parse() {
            // Parse code
            TokenParser parser(mainFile->getCode());

            while (true) {
                auto token = parser.peekToken();

                if (token == L"") {
                    break;
                } else if (token == L"module") {
                    parseModule(parser);
                } else {
                    return parser.throwError(L"Unexpected token " + token.token);
                }
            }

            parsed = true;
        }

        void Parser::parseModule(TokenParser &parser) {
            auto module = make_unique<Module>();
            module->Parse(parser);
            modules.push_back(std::move(module));
        }

        CodeFile &Parser::loadFile(const std::wstring &filePath) {
            codeFiles.push_back(std::make_unique<CodeFile>(filePath, *this));
            auto &codeFile = codeFiles.back();
            return *codeFile;
        }

        const std::vector<std::unique_ptr<Module>> &Parser::getModules() const {
            assert(parsed); // Code not parsed yet!

            return modules;
        }
    }
}