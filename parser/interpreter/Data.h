//
// Created by Nils van Eijk on 03-04-18.
//

#ifndef XLANG_DATA_H
#define XLANG_DATA_H


#include "../../utils/non_copyable.h"
#include "../../utils/Utils.h"

#include <vector>
#include <string>

class Data : public non_copyable {
private:
    std::vector<unsigned char> data;

public:
    Data& operator =(const std::wstring& str) {
        auto utf8Str = Utils::wstring_to_utf8(str);

        data.insert(data.begin(), utf8Str.begin(), utf8Str.end());
        return *this;
    }

    template <typename T>
    bool operator ==(const T& other) const {
        if (other.size() != data.size()) {
            return false;
        } else {
            for (unsigned long i = 0; i < data.size(); i++) {
                if (data[i] != other[i]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator ==(const Data& other) const {

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

    bool operator != (const Data& other) const {
        return !(other == *this);
    }

    const std::vector<unsigned char> &getData() const {
        return data;
    }
};


#endif //XLANG_DATA_H
