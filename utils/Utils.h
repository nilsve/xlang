//
// Created by Nils van Eijk on 20-02-18.
//

#ifndef XLANG_UTILS_H
#define XLANG_UTILS_H

#include <string>

class Utils {
private:
    Utils() = default;
public:
    static std::wstring readFile(const std::wstring& fileName);

    static bool stringReplace(std::wstring &str, const std::wstring &from, const std::wstring &to);

    static std::string wstring_to_utf8 (const std::wstring& str);
    static std::wstring utf8_to_wstring (const std::string& str);
};


#endif //XLANG_UTILS_H
