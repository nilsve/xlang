//
// Created by Nils van Eijk on 20-02-18.
//

#ifndef XLANG_NON_COPYABLE_H
#define XLANG_NON_COPYABLE_H


class non_copyable
{
protected:
    non_copyable() = default;
    ~non_copyable() = default;
public:
    non_copyable(non_copyable const &) = delete;
    void operator=(non_copyable const &x) = delete;
};

#endif //XLANG_NON_COPYABLE_H
