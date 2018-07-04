//
// Created by Nils van Eijk on 30-03-18.
//

#include "NasmX86Assembler.h"
#include "../../instructions/JmpInstruction.h"
#include "../../instructions/CallInstruction.h"
#include "../../../interpreter/Variable.h"

#include "X86AssignInstruction.h"
#include "X86CallInstruction.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

namespace xlang {
    namespace compiler {
        namespace assemblers {

            using namespace std;
            using namespace x86;

            int NasmX86Assembler::getVariableIndex(int variableIndex) const {
                if (variableIndex >= 0) {
                    return variableIndex;
                } else {
                    return variableIndex - 1;
                }
            }

            wstring NasmX86Assembler::assembleInstruction(const compiler::instructions::Instruction &instruction) const {

                if (X86AssignInstruction::isType(&instruction)) {
                    return assignInstructionAssembler->Assemble(*dynamic_cast<const instructions::AssignInstruction*>(&instruction));
                } else if (X86CallInstruction::isType(&instruction)) {
                    return callInstructionAssembler->Assemble(*dynamic_cast<const instructions::CallInstruction*>(&instruction));
                } else if (X86JmpInstruction::isType(&instruction)) {
                    return jmpInstructionAssembler->Assemble(*dynamic_cast<const instructions::JmpInstruction*>(&instruction));
                }

                throw invalid_argument("Instruction not implemented!");
            }

            wstring NasmX86Assembler::assembleFunctionEnd(const interpreter::Function &function) const {
                return L"mov esp, ebp\n"
                       L"pop ebp\n"
                       L"ret " + (function.getCallingConvention() == interpreter::CallingConvention::CDECL ? to_wstring(
                        function.getParameters().size() * getRegisterSize()) : L"");
            }

            wstring NasmX86Assembler::assembleScopeStart(const interpreter::Scope &scope) const {
                auto result = AssemblerBase::assembleScopeStart(scope);

                auto scopeReservation = scope.getVariables().size() * getRegisterSize();
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

                auto scopeReservation = scope.getVariables().size() * getRegisterSize();
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

            long NasmX86Assembler::getRegisterSize() const {
                return 4;
            }
        }
    }
}
