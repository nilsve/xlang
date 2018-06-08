//
// Created by Nils van Eijk on 04-04-18.
//

#include "Data.h"

namespace xlang {
    namespace interpreter {

        using namespace utils;

        unsigned long Data::highestDataId = 0;

        Data &Data::operator=(const std::wstring &str) {
            auto utf8Str = Utils::wstring_to_utf8(str);

            data.insert(data.begin(), utf8Str.begin(), utf8Str.end());
            return *this;
        }

        bool Data::operator==(const Data &other) const {

            return *this == other.data;

            if (other.data.size() != data.size()) {
                return false;
            } else {
                for (unsigned long i = 0; i < data.size(); i++) {
                    if (data[i] != other.data[i]) {
                        return false;
                    }
                }
            }

            return true;
        }

        bool Data::operator!=(const Data &other) const {
            return !(other == *this);
        }

        const std::vector<unsigned char> &Data::getData() const {
            return data;
        }

        std::wstring Data::getUniqueDataId() {
            return L"d_" + std::to_wstring(highestDataId++);
        }

        const std::wstring &Data::getDataId() const {
            return dataId;
        }

        bool Data::getIsNumber() const {
            return isNumber;
        }

        std::wstring Data::getDataAsString() const {
            return std::wstring(data.begin(), data.end()) + L"";
        }
    }
}