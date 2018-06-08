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

            using namespace std;

            const long REGISTER_SIZE = 4;

            int getVariableIndex(int variableIndex) {
                if (variableIndex >= 0) {
                    return variableIndex;
                } else {
                    return variableIndex - 1;
                }
            }

            wstring NasmX86Assembler::assembleInstruction(const compiler::instructions::Instruction &instruction) const {
                if (auto callInstruction = dynamic_cast<const compiler::instructions::CallInstruction *>(&instruction)) {

                    wstring result;

                    for (auto &parameter : callInstruction->getParameters()) {
                        result += L"push DWORD [ebp + " + to_wstring(parameter.variable.getVariableIndex()) + L"]\n";
                    }

                    return result + L"call " + callInstruction->getTarget()->getFullPath();
                } else if (auto assignInstruction = dynamic_cast<const compiler::instructions::AssignInstruction *>(&instruction)) {
                    return assembleAssignInstruction(*assignInstruction);
                } else if (auto jmpInstruction = dynamic_cast<const compiler::instructions::JmpInstruction *>(&instruction)) {
                    return L"jmp " + jmpInstruction->getTarget()->getFullPath();
                }

                throw invalid_argument("Instruction not implemented!");
            }

            wstring NasmX86Assembler::assembleAssignInstruction(const instructions::AssignInstruction &assignInstruction) const {
                wstring result;
                if (auto target = assignInstruction.getTarget()) {

                    wstring source;

                    if (auto data = assignInstruction.getData()) {
                        if (data->getIsNumber()) {
                            result += L"mov DWORD [ebp + " + to_wstring(getVariableIndex(target->getVariableIndex()) * REGISTER_SIZE) + L"], " + data->getDataAsString();
                        } else {
                            result +=  L"mov DWORD eax, " + data->getDataId() + L"\n";
                                     L"mov DWORD [ebp + " + to_wstring(getVariableIndex(target->getVariableIndex()) * REGISTER_SIZE) + L"], eax";
                        }

                    } else if (auto sourceVariable = assignInstruction.getSourceVariable()) {
                        result += L"mov DWORD eax, [ebp + " + to_wstring(getVariableIndex(sourceVariable->getVariableIndex()) * REGISTER_SIZE) + L"]\n"
                               L"mov DWORD [ebp + " + to_wstring(getVariableIndex(target->getVariableIndex()) * REGISTER_SIZE) + L"], eax";
                    } else {
                        assert(false);
                    }
                } else {
                    utils::Utils::throwError("Target empty for assignment instruction!");
                }

                return result;
            }

            wstring NasmX86Assembler::assembleFunctionEnd(const interpreter::Function &function) const {
                return L"mov esp, ebp\n"
                       L"pop ebp\n"
                       L"ret " + (function.getCallingConvention() == interpreter::CallingConvention::CDECL ? to_wstring(
                        function.getParameters().size() * REGISTER_SIZE) : L"");
            }

            wstring NasmX86Assembler::assembleScopeStart(const interpreter::Scope &scope) const {
                auto result = AssemblerBase::assembleScopeStart(scope);

                unsigned int scopeReservation = scope.getVariables().size() * REGISTER_SIZE;
                if (scopeReservation > 0) {
                    result += L"\n"
                              L"sub esp, " + to_wstring(scopeReservation);
                }

                return result;
            }

            wstring NasmX86Assembler::assembleFunctionStart(const interpreter::Function &function) const {
                auto result = AssemblerBase::assembleFunctionStart(function);
                result += L"\n"
                          L"push ebp\n"
                          L"mov ebp, esp";
                return result;
            }

            wstring NasmX86Assembler::assembleScopeEnd(const interpreter::Scope &scope) const {
                wstring result = L"ret";

                unsigned int scopeReservation = scope.getVariables().size() * REGISTER_SIZE;
                if (scopeReservation > 0) {
                    result = L"add esp, " + to_wstring(scopeReservation) + L"\n" + result;
                }

                return result;
            }

            wstring NasmX86Assembler::assembleData(const interpreter::Data &data) const {
                wstringstream stream;
                stream << data.getDataId() << L": db ";

                for (auto chr : data.getData()) {
                    stream << L"0x" << hex << setw(2) << setfill(L'0') << int(chr) << L",";
                }

                stream << L"0x0";
                return stream.str();
            }
        }
    }
}
