//
// Created by Nils van Eijk on 20-02-18.
//

#include "Utils.h"
#include "../parser/interpreter/Data.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <vector>

using namespace std;

std::wstring Utils::readFile(const std::wstring& fileName) {
    ifstream file(Utils::wstring_to_utf8(fileName).c_str());
    if (!file.is_open()) {
        Utils::throwError(L"Couldn't open file " + fileName + L": " + utf8_to_wstring(strerror(errno)));
    }

    stringstream wss;
    wss << file.rdbuf();
    return Utils::utf8_to_wstring(wss.str());

}

std::string Utils::wstring_to_utf8 (const std::wstring& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}

std::wstring Utils::utf8_to_wstring (const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
}

bool Utils::stringReplace(std::wstring& str, const std::wstring& from, const std::wstring& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::wstring::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::wstring Utils::generateUuid(unsigned int length) {
    static std::wstring characters = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    wstring output;

    for (unsigned int i = 0; i < length; i++) {
        output += characters[rand() % characters.length()];
    }

    return output;
}

void Utils::throwError(std::wstring message) {
    return throwError(Utils::wstring_to_utf8(message));
}

void Utils::throwError(std::string message) {
    throw std::invalid_argument(message.c_str());
}

void Utils::Log(const std::string& message) {
    return Log(Utils::utf8_to_wstring(message));
}

void Utils::Log(const std::wstring& message) {
    std::wcout << message;
}
