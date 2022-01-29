cmake_minimum_required(VERSION 3.0.0)
project(Processor VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CPU CPU.cpp src/stack_class.cpp src/CPU_class.cpp)
add_executable(Assembler Assembler.cpp src/table_class.cpp src/array_class.cpp)
add_executable(Disassembler Disassembler.cpp src/list_class.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
