//
// Created by Nils van Eijk on 20-02-18.
//

#include "TokenParser.h"
#include "Parser.h"
#include "../../utils/Utils.h"

#include <string>
#include <vector>
#include <set>

#include <iostream>

using namespace std;

namespace xlang {
    namespace interpreter {

        using namespace utils;

        void CodeFile::Preprocess() {
            TokenParser parser(code);
            while (true) {
                const Token token = parser.getToken(true);

                if (!token.isStringLiteral) {
                    if (token == L"#") {
                        handlePreProcessor(parser);
                    }
                }

                if (token == L"") {
                    break;
                }
            }
        }

        void CodeFile::Load() {
            Preprocess();
        }

        std::wstring CodeFile::resolvePath(const std::wstring relativePath) const {
            char realPath[PATH_MAX];

            string shortPath = utils::Utils::wstring_to_utf8(this->parser.getWorkspace() + relativePath);

            realpath(shortPath.c_str(), realPath);

            return Utils::utf8_to_wstring(std::string(realPath));
        }

        CodeFile::CodeFile(std::wstring relativePath, Parser &parser) : parser(parser), relativePath(relativePath) {
            this->code = Utils::readFile(resolvePath(relativePath));
        }

        const std::wstring &CodeFile::getCode() const {
            return code;
        }

        void CodeFile::handlePreProcessor(TokenParser &parser) {
            auto token = parser.getToken();
            if (token == L"include") {
                const Token fileToken = parser.getToken(true);
                if (!fileToken.isStringLiteral) {
                    parser.throwError("Expected a string literal after #include");
                } else {
                    // Fix import
                    auto &codeFile = this->parser.loadFile(fileToken.token);
                    code.replace(token.position - 1, fileToken.position + fileToken.token.length() + 2,
                                 codeFile.code);
                }
            } else {
                parser.throwError(L"Unknown preprocessor statement " + token.token);
            }
        }
    }
}