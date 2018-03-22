//
// Created by Nils van Eijk on 20-02-18.
//

#include "Parser.h"
#include "../utils/Utils.h"
#include "TokenParser.h"
#include "interpreter/Module.h"

#include <string>
#include <exception>
#include <assert.h>

using namespace std;

Parser::Parser(const std::wstring& workspace, const std::wstring& mainFilePath) : workspace(workspace) {
    auto codeFile = loadFile(mainFilePath);
    mainFile = codeFile;
    mainFile->Load();
}

void Parser::Parse() {
    // Parse code
    TokenParser parser(mainFile->getCode());

    while(true) {
        auto token = parser.getToken(false);

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

void Parser::parseModule(TokenParser& parser) {
    shared_ptr<Module> module = make_shared<Module>();
    module->Parse(parser);
    modules.push_back(module);
}

std::shared_ptr<CodeFile> Parser::loadFile(const std::wstring& filePath) {
    auto codeFile = std::make_shared<CodeFile>(filePath, *this);
    codeFiles.push_back(codeFile);
    codeFile->Load();
    return codeFile;
}

const std::vector<std::shared_ptr<Module>>& Parser::getModules() const {
    assert(parsed); // Code not parsed yet!

    return modules;
}
