//
// Created by Nils van Eijk on 22-03-18.
//

#include "Assembler.h"
#include "../../utils/Utils.h"

#include <map>

using namespace std;

void Assembler::Assemble() {
    const auto& modules = parser.getModules();

    assembleModules(modules);

    if (auto module = findModule(modules, L"main")) {
        auto function = findFunction(*module, L"main");
    }

}

void Assembler::assembleModules(const std::vector<std::unique_ptr<Module>>& modules) {
    for (auto& module : modules) {
        assembleModule(*module);
    }
}

void Assembler::assembleModule(const Module& module) {
    for (auto& function : module.getFunctions()) {
        functionMap[module.getModuleName() + L"." + function->getFunctionName()] = currentOutputOffset;
        assembleFunction(*function);
    }
}

void Assembler::assembleFunction(const Function& function) {

    assembleScope(*function.getRootScope());

}

void Assembler::assembleScope(const Scope& scope) {

}

const Module* Assembler::findModule(const std::vector<std::unique_ptr<Module>>& modules, std::wstring moduleName) const {
    for (auto& module : modules) {
        if (module->getModuleName() == moduleName) {
            return module.get();
        }
    }

    return nullptr;
}

const Function* Assembler::findFunction(const Module &module, std::wstring functionName) const {
    for (auto& function : module.getFunctions()) {
        if (function->getFunctionName() == functionName) {
            return function.get();
        }
    }

    return nullptr;
}

void Assembler::throwError(std::wstring message) const {
    return throwError(Utils::wstring_to_utf8(message));
}

void Assembler::throwError(std::string message) const {
    throw std::invalid_argument(message.c_str());
}

Assembler::Assembler(const Parser& _parser) : parser(_parser) {
    output.reserve(2048);
}

unsigned long Assembler::appendOutput(std::vector<unsigned char> instructions) {
    output.insert(output.end(), instructions.begin(), instructions.end());
    return currentOutputOffset = output.size();
}
