//
// Created by Nils van Eijk on 21-02-18.
//

#ifndef XLANG_TOKENPARSER_H
#define XLANG_TOKENPARSER_H

#include <string>
#include <jmorecfg.h>
#include "../utils/non_copyable.h"

struct Token {
    bool isStringLiteral = false;
    std::wstring token;
    unsigned long position = 0;

    bool operator==(const std::wstring& other) const;
    bool operator!=(const std::wstring& other) const;
};

class TokenParser : public non_copyable {
private:
    const std::wstring& code;
    unsigned long position = 0;

    static bool isWhitespace(wchar_t chr);
    static wchar_t getStringLiteral(wchar_t chr);
    static bool isSpecialChar(wchar_t chr);
public:
    TokenParser(const std::wstring& code) : code(code) {}
    const Token getToken(bool allowStringLiteral = true);
    Token peekToken(bool allowStringLiteral = true);

    void throwError(std::wstring message) const;
    void throwError(std::string message) const;

    void eatToken();


};


#endif //XLANG_TOKENPARSER_H