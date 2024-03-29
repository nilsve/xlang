//
// Created by Nils van Eijk on 20-02-18.
//

#ifndef XLANG_UTILS_H
#define XLANG_UTILS_H

#include <string>
#include <vector>

namespace xlang {
    namespace utils {

        class Utils {
        private:
            Utils() = default;

        public:
            static std::wstring readFile(const std::wstring &fileName);
            static bool stringReplace(std::wstring &str, const std::wstring &from, const std::wstring &to);
            static std::string wstring_to_utf8(const std::wstring &str);
            static std::wstring utf8_to_wstring(const std::string &str);
            static std::wstring generateUuid(unsigned int length = 5);
            static void Log(const std::wstring &message);
            static void Log(const std::string &message);
            static void throwError(std::wstring message);
            static void throwError(std::string message);

            template <typename T>
            static bool isNumber(T s) {
                return !s.empty() && std::find_if(s.begin(),
                                                  s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
            }
        };
    }
}
#endif //XLANG_UTILS_H
