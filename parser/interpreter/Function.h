//
// Created by Nils van Eijk on 02-03-18.
//

#ifndef XLANG_FUNCTION_H
#define XLANG_FUNCTION_H


#include "../TokenParser.h"
#include "Variable.h"
#include "Scope.h"

#include <memory>
#include <vector>

enum class CallingConvention {
    cdecl,
    stdcall,
    unknown,
};

class Module;

class Function : public non_copyable  {
private:
    const Module* parent = nullptr;

    std::wstring functionName;
    CallingConvention callingConvention;

    std::vector<std::unique_ptr<Variable>> parameters;
    std::unique_ptr<Variable> returnVariable;

    std::unique_ptr<Scope> rootScope;

    void parseHeader(TokenParser& parser);
    void parseBody(TokenParser& parser);

    static CallingConvention getCallingConvention(const std::wstring& convention);
public:
    Function(const Module* _parent) : parent(_parent) {}
    void Parse(TokenParser& parser);

    const std::wstring &getFunctionName() const;

    const Module *getParent() const;

    CallingConvention getCallingConvention() const;
    const std::vector<std::unique_ptr<Variable>> &getParameters() const;
    const std::unique_ptr<Variable> &getReturnVariable() const;
    const std::unique_ptr<Scope> &getRootScope() const;
};


#endif //XLANG_FUNCTION_H
