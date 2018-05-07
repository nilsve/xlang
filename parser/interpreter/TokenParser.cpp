//
// Created by Nils van Eijk on 21-02-18.
//

#include "TokenParser.h"
#include "../../utils/Utils.h"
#include <iostream>

using namespace std;

namespace xlang {
    namespace interpreter {

        const Token TokenParser::peekToken(bool allowStringLiteral) {
            auto oldPosition = position;
            peekedToken = getToken(allowStringLiteral);
            afterPeekPosition = position;
            position = oldPosition;
            tokenAvailable = true;

            return peekedToken;
        }

        void TokenParser::eatToken() {
            tokenAvailable = false;
            position = afterPeekPosition;
        }

        bool TokenParser::isWhitespace(wchar_t chr) {
            return chr == L' ' || chr == L'\t' || chr == L'\n' || chr == L'\r';
        }

        const Token TokenParser::getToken(bool allowStringLiteral) {

            if (tokenAvailable) {
                position = afterPeekPosition;
                tokenAvailable = false;
                return std::move(peekedToken);
            }

            Token token;
            token.position = position;

            wchar_t stringLiteral = 0;

            for (; position < code.length(); position++) {
                const wchar_t chr = code[position];

                if (stringLiteral || !isWhitespace(chr)) {

                    if (!stringLiteral && getStringLiteral(chr)) {
                        // Begin string literal

                        if (!allowStringLiteral) {
                            throwError(L"Unexpected string literal!");
                        }

                        token.isStringLiteral = stringLiteral = chr;
                        continue;
                    } else if (!stringLiteral && token.token.length() > 0) {
                        // Check for special characters

                        if (isSpecialChar(chr)) {
                            break;
                        }

                    } else if (stringLiteral != 0) {
                        if (stringLiteral == chr) {
                            // Einde string literal
                            position++;
                            break;
                        } else if (chr == '\n') {
                            // Fout!
                            throwError(L"Unexpected newline in string literal!");
                        }
                    } else if (isSpecialChar(chr)) {
                        position++;
                        token.token += chr;
                        break;
                    }

                    token.token += chr;

                } else if (token.token.length() > 0) {
                    position++;
                    break;
                }
            }

            return token;
        }

        bool TokenParser::isSpecialChar(wchar_t chr) {
            // _ char is allowed
            return !((chr == L'_') || (chr >= L'a' && chr <= L'z') || (chr >= L'A' && chr <= L'Z') || (chr >= L'0' && chr <= L'9'));
        }

        wchar_t TokenParser::getStringLiteral(wchar_t chr) {
            if (chr == L'\'' || chr == '"') {
                return chr;
            } else {
                return 0;
            }
        }

        std::wstring TokenParser::readUntill(wchar_t character) {
            auto startPos = position;
            for (; position < code.length(); position++) {
                char chr = code[position];
                if (chr == character) {
                    return code.substr(startPos, position - startPos);
                }
            }

            throwError(std::wstring(L"End character ") + character + std::wstring(L"not found!"));
        }

        // TODO: Refactor this trash...
        void TokenParser::throwError(const std::wstring &message) const {
            wstring text;
            text.reserve(256);// magic number...
            unsigned short newLineCount = 0;
            for (auto i = position; i > 0; i--) {
                if (code[i] == L'\n') {
                    newLineCount++;
                    if (newLineCount > 1) {
                        break;
                    } else if (newLineCount == 1) {
                        text += L">>>>";
                    }
                }

                text += code[i];
            }

            reverse(text.rbegin(), text.rend());

            newLineCount = 0;
            for (auto i = position + 1; i < code.length(); i++) {
                if (code[i] == L'\n') {
                    newLineCount++;
                    if (newLineCount > 1) {
                        break;
                    }
                }

                text += code[i];
            }

            return utils::Utils::throwError(message + L"\n\n" + text);
        }

        bool Token::operator==(const std::wstring &other) const {
            return this->token == other;
        }

        bool Token::operator!=(const std::wstring &other) const {
            return this->token != other;
        }
    }
}