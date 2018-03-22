//
// Created by Nils van Eijk on 20-02-18.
//

#ifndef XLANG_PARSER_H
#define XLANG_PARSER_H

#include <vector>
#include <string>
#include <memory>
#include "../utils/non_copyable.h"
#include "CodeFile.h"
#include "TokenParser.h"
#include "interpreter/Module.h"

class Parser : public non_copyable {
private:
    bool parsed = false;

    std::vector<std::shared_ptr<CodeFile>> codeFiles;
    std::vector<std::shared_ptr<Module>> modules;

    std::shared_ptr<CodeFile> mainFile;

    void parseModule(TokenParser &parser);

public:
    const std::wstring workspace;

    Parser(const std::wstring& workspace, const std::wstring& mainFilePath);
    void Parse();

    std::shared_ptr<CodeFile> loadFile(const std::wstring& filePath);

    const std::vector<std::shared_ptr<Module>>& getModules() const;
};


#endif //XLANG_PARSER_H
