cmake_minimum_required(VERSION 3.8)
project(xlang)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FILES main.cpp parser/Parser.cpp parser/Parser.h utils/Utils.cpp utils/Utils.h parser/CodeFile.cpp parser/CodeFile.h utils/non_copyable.h parser/TokenParser.cpp parser/TokenParser.h parser/interpreter/Module.cpp parser/interpreter/Module.h parser/interpreter/Function.cpp parser/interpreter/Function.h parser/interpreter/Variable.cpp parser/interpreter/Variable.h parser/interpreter/Structure.cpp parser/interpreter/Structure.h parser/interpreter/Scope.cpp parser/interpreter/Scope.h parser/compiler/instructions/Instruction.cpp parser/compiler/instructions/Instruction.h parser/compiler/instructions/JmpInstruction.cpp parser/compiler/instructions/JmpInstruction.h parser/compiler/Compiler.h parser/compiler/instructions/CallInstruction.cpp parser/compiler/instructions/CallInstruction.h parser/compiler/assemblers/NasmAssembler.cpp parser/compiler/assemblers/NasmAssembler.h parser/compiler/assemblers/AssemblerBase.cpp parser/compiler/assemblers/AssemblerBase.h parser/compiler/InstructionValidator.cpp parser/compiler/InstructionValidator.h)
add_executable(xlang ${SOURCE_FILES})