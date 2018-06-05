//
// Created by Nils van Eijk on 30-03-18.
//

#include "NasmX86Assembler.h"
#include "../instructions/CallInstruction.h"
#include "../instructions/AssignInstruction.h"
#include "../instructions/JmpInstruction.h"
#include "../../interpreter/Variable.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

namespace xlang {
    namespace compiler {
        namespace assemblers {

            const long REGISTER_SIZE = 4;

            int getVariableIndex(int variableIndex) {
                if (variableIndex >= 0) {
                    return variableIndex;
                } else {
                    return variableIndex - 1;
                }
            }

            std::wstring NasmX86Assembler::assembleInstruction(const compiler::instructions::Instruction &instruction) const {
                if (auto callInstruction = dynamic_cast<const compiler::instructions::CallInstruction *>(&instruction)) {

                    std::wstring result;

                    for (auto &parameter : callInstruction->getParameters()) {
                        result += L"push DWORD [ebp + " + std::to_wstring(parameter.variable.getVariableIndex()) + L"]\n";
                    }

                    return result + L"call " + callInstruction->getTarget()->getFullPath();
                } else if (auto assignInstruction = dynamic_cast<const compiler::instructions::AssignInstruction *>(&instruction)) {

                    if (auto target = assignInstruction->getTarget()) {
                        if (auto data = assignInstruction->getData()) {
                            if (data->getIsNumber()) {
                                return  L"mov DWORD [ebp + " + std::to_wstring(getVariableIndex(target->getVariableIndex()) * REGISTER_SIZE) + L"], " + data->getDataAsString();
                            } else {
                                return  L"mov DWORD eax, " + data->getDataId() + L"\n"
                                        L"mov DWORD [ebp + " + std::to_wstring(getVariableIndex(target->getVariableIndex()) * REGISTER_SIZE) + L"], eax";
                            }

                        } else if (auto sourceVariable = assignInstruction->getSourceVariable()) {
                            return L"mov DWORD eax, [ebp + " + std::to_wstring(getVariableIndex(sourceVariable->getVariableIndex()) * REGISTER_SIZE) + L"]"
                                   L"mov DWORD [ebp + " + std::to_wstring(getVariableIndex(target->getVariableIndex()) * REGISTER_SIZE) + L"], eax";
                        } /* else if (auto& constSimpleType = assignInstruction->getConstSimpleType()) {
                            std::wstring result = L"mov ";
                            switch (constSimpleType->getDataType()) {
                                case interpreter::DataType::DOUBLE:
                                case interpreter::DataType::FLOAT:
                                case interpreter::DataType::INT:
                                    result += L"DWORD";
                                    break;
                                case interpreter::DataType::CHAR:
                                    assert(false); // TODO
                                    break;
                                case interpreter::DataType::UNKNOWN:
                                    assert(false);
                            }
                            return result + L" [ebp + " + std::to_wstring(getVariableIndex(target->getVariableIndex()) * REGISTER_SIZE) + L"], " + constSimpleType->constSimpleData;
                        }*/ else {
                            assert(false);
                        }
                    } else {
                        utils::Utils::throwError("Target empty for assignment instruction!");
                    }
                } else if (auto jmpInstruction = dynamic_cast<const compiler::instructions::JmpInstruction *>(&instruction)) {
                    return L"jmp " + jmpInstruction->getTarget()->getFullPath();
                }

                throw std::invalid_argument("Instruction not implemented!");
            }

            std::wstring NasmX86Assembler::assembleFunctionEnd(const interpreter::Function &function) const {
                return L"mov esp, ebp\n"
                       L"pop ebp\n"
                       L"ret " + (function.getCallingConvention() == interpreter::CallingConvention::CDECL ? std::to_wstring(
                        function.getParameters().size() * REGISTER_SIZE) : L"");
            }

            std::wstring NasmX86Assembler::assembleScopeStart(const interpreter::Scope &scope) const {
                auto result = AssemblerBase::assembleScopeStart(scope);

                unsigned int scopeReservation = scope.getVariables().size() * REGISTER_SIZE;
                if (scopeReservation > 0) {
                    result += L"\n"
                              L"sub esp, " + std::to_wstring(scopeReservation);
                }

                return result;
            }

            std::wstring NasmX86Assembler::assembleFunctionStart(const interpreter::Function &function) const {
                auto result = AssemblerBase::assembleFunctionStart(function);
                result += L"\n"
                          L"push ebp\n"
                          L"mov ebp, esp";
                return result;
            }

            std::wstring NasmX86Assembler::assembleScopeEnd(const interpreter::Scope &scope) const {
                std::wstring result = L"ret";

                unsigned int scopeReservation = scope.getVariables().size() * REGISTER_SIZE;
                if (scopeReservation > 0) {
                    result = L"add esp, " + std::to_wstring(scopeReservation) + L"\n" + result;
                }

                return result;
            }

            std::wstring NasmX86Assembler::assembleData(const interpreter::Data &data) const {
                std::wstringstream stream;
                stream << data.getDataId() << L": db ";

                for (auto chr : data.getData()) {
                    stream << L"0x" << std::hex << std::setw(2) << std::setfill(L'0') << int(chr) << L",";
                }

                stream << L"0x0";
                return stream.str();
            }
        }
    }
}
