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
                            throwError("Unexpected string literal!");
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
                            throwError("Unexpected newline in string literal!");
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

        bool Token::operator==(const std::wstring &other) const {
            return this->token == other;
        }

        bool Token::operator!=(const std::wstring &other) const {
            return this->token != other;
        }
    }
}