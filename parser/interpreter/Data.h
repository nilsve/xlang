//
// Created by Nils van Eijk on 03-04-18.
//

#ifndef XLANG_DATA_H
#define XLANG_DATA_H


#include "../../utils/non_copyable.h"
#include "../../utils/Utils.h"

#include <vector>
#include <string>

namespace xlang {
    namespace interpreter {

        enum class DataStorageMode {
            SCOPE,
            SECTION,
        };

        class Data : public utils::non_copyable {
        private:
            static unsigned long highestDataId;
            const std::wstring dataId;
            const bool isNumber = false;
            std::vector<unsigned char> data;

            static std::wstring getUniqueDataId();

        public:
            Data(bool _isNumber) : dataId(Data::getUniqueDataId()), isNumber(_isNumber) {}

            Data &operator=(const std::wstring &str);

            bool getIsNumber() const;

            template<typename T>
            bool operator==(const T &other) const {
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

            std::wstring getDataAsString() const;

            bool operator==(const Data &other) const;
            bool operator!=(const Data &other) const;

            const std::vector<unsigned char> &getData() const;

            const std::wstring &getDataId() const;
        };
    }
}

#endif //XLANG_DATA_H
