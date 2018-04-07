//
// Created by Nils van Eijk on 21-02-18.
//

#ifndef XLANG_TOKENPARSER_H
#define XLANG_TOKENPARSER_H

#include <string>
#include "../../utils/non_copyable.h"
#include "../../utils/Utils.h"

namespace xlang {
    namespace interpreter {

        struct Token {
            bool isStringLiteral = false;
            std::wstring token;
            unsigned long position = 0;

            bool operator==(const std::wstring &other) const;

            bool operator!=(const std::wstring &other) const;
        };

        class TokenParser : public utils::non_copyable {
        private:
            const std::wstring &code;
            unsigned long position = 0;

            bool tokenAvailable = false;
            unsigned long afterPeekPosition = 0;
            Token peekedToken;

            static bool isWhitespace(wchar_t chr);

            static wchar_t getStringLiteral(wchar_t chr);

            static bool isSpecialChar(wchar_t chr);

        public:
            explicit TokenParser(const std::wstring &code) : code(code) {}

            const Token getToken(bool allowStringLiteral = false);
            const Token peekToken(bool allowStringLiteral = false);
            std::wstring readUntill(wchar_t character);

            template<typename T>
            void throwError(T message) const {
                return utils::Utils::throwError(message);
            }

            void eatToken();

        };
    }
}

#endif //XLANG_TOKENPARSER_H
