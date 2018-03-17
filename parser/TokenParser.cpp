//
// Created by Nils van Eijk on 21-02-18.
//

#include "TokenParser.h"
#include "../utils/Utils.h"
#include <iostream>

using namespace std;

Token TokenParser::peekToken(bool allowStringLiteral) {
    auto oldPosition = position;
    auto token = getToken();
    position = oldPosition;
    return token;
}

void TokenParser::eatToken() {
    getToken();
}

bool TokenParser::isWhitespace(wchar_t chr) {
    return chr == L' ' || chr == L'\t' || chr == L'\n' || chr == L'\r';
}

const Token TokenParser::getToken(bool allowStringLiteral) {
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

                if (!((chr >= L'a' && chr <= L'z') || (chr >= L'A' && chr <= L'Z') || (chr >= 0 && chr <= L'9'))) {
                    break;
                }

            } else  if (stringLiteral != 0) {
                if (stringLiteral == chr) {
                    // Einde string literal
                    position++;
                    break;
                } else if (chr == '\n') {
                    // Fout!
                    throw new exception();
                }
            }

            token.token += chr;

        } else if (token.token.length() > 0) {
            position++;
            break;
        }
    }

    return token;
}

wchar_t TokenParser::getStringLiteral(wchar_t chr) {
    if (chr == L'\'' || chr == '"') {
        return chr;
    } else {
        return 0;
    }
}

void TokenParser::throwError(std::wstring message) const {
    return throwError(Utils::wstring_to_utf8(message));
}

void TokenParser::throwError(std::string message) const {
    throw std::invalid_argument(message.c_str());
}