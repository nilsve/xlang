cmake_minimum_required(VERSION 3.8)
project(xlang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

set(SOURCE_FILES main.cpp parser/interpreter/Parser.cpp parser/interpreter/Parser.h utils/Utils.cpp utils/Utils.h parser/interpreter/CodeFile.cpp parser/interpreter/CodeFile.h utils/non_copyable.h parser/interpreter/TokenParser.cpp parser/interpreter/TokenParser.h parser/interpreter/Module.cpp parser/interpreter/Module.h parser/interpreter/Function.cpp parser/interpreter/Function.h parser/interpreter/Variable.cpp parser/interpreter/Variable.h parser/interpreter/Structure.cpp parser/interpreter/Structure.h parser/interpreter/Scope.cpp parser/interpreter/Scope.h parser/compiler/instructions/Instruction.h parser/compiler/instructions/JmpInstruction.h parser/compiler/Compiler.h parser/compiler/instructions/CallInstruction.h parser/compiler/assemblers/x86/NasmX86Assembler.cpp parser/compiler/assemblers/x86/NasmX86Assembler.h parser/compiler/assemblers/AssemblerBase.h parser/compiler/InstructionValidator.cpp parser/compiler/InstructionValidator.h parser/interpreter/Data.h parser/compiler/instructions/AssignInstruction.h parser/interpreter/Data.cpp parser/compiler/Target.h parser/compiler/Target.cpp parser/compiler/WeakTarget.cpp parser/compiler/WeakTarget.h parser/compiler/StrongTarget.cpp parser/compiler/StrongTarget.h parser/compiler/instructions/ReturnInstruction.h parser/interpreter/Container.cpp parser/interpreter/Container.h parser/interpreter/VariableLink.h parser/compiler/assemblers/x86/X86AssignInstruction.h parser/compiler/assemblers/InstructionAssembler.h parser/compiler/assemblers/x86/X86CallInstruction.h parser/compiler/assemblers/x86/X86JmpInstruction.h)
add_executable(xlang ${SOURCE_FILES})
target_link_libraries(xlang
        ${GTKMM_LIBRARIES}  )