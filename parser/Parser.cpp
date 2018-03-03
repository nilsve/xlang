//
// Created by Nils van Eijk on 20-02-18.
//

#include "Parser.h"
#include "../utils/Utils.h"
#include "TokenParser.h"
#include "interpreter/Module.h"

#include <string>
#include <exception>

using namespace std;

Parser::Parser(const std::wstring& workspace, const std::wstring& mainFilePath) : workspace(workspace) {
    auto codeFile = loadFile(mainFilePath);
    mainFile = codeFile;
    mainFile->Load();

    // All imports have been resolved at this stage.
    Parse();
}

void Parser::Parse() {
    // Parse code
    TokenParser parser(mainFile->getCode());

    while(true) {
        auto token = parser.getToken();

        if (token.token == L"module") {
            parseModule(parser);
        } else {
            return parser.throwError(L"Unexpected token " + token.token);
        }
    }
}

void Parser::parseModule(TokenParser& parser) {
    shared_ptr<Module> module = make_shared<Module>();
    module->Parse(parser);
    modules.push_back(module);
}

void Parser::validateRootToken(const TokenParser& parser, Token& token) {
    if (token.isStringLiteral) {
        parser.throwError("Unexpected string literal!");
    }
}

std::shared_ptr<CodeFile> Parser::loadFile(const std::wstring& filePath) {
    auto codeFile = std::make_shared<CodeFile>(filePath, *this);
    codeFiles.push_back(codeFile);
    codeFile->Load();
    return codeFile;
}
