cmake_minimum_required(VERSION 3.10.2)
project(Task_4_cpu)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -Wconversion -Wpedantic -Wno-unused-function)

include_directories(. .. cpp cpp/utils)

set(lang_includes
        cpp/utils/console_args/console_args.cpp
        cpp/utils/checked_actions/checked_io.cpp
        cpp/utils/logging/logging.cpp
        cpp/lexer/lexer.cpp
        cpp/lexer/token/token.cpp
        cpp/parser/parser.cpp
        cpp/parser/nodes/nodes.cpp
        cpp/parser/nodes/command_type.cpp
        ../minilog/minilog.c
        ../ministringutils/ministringutils.cpp
        ../minitools/error.c
)

add_executable(asm
        cpp/assembler/main.cpp
        cpp/assembler/assembler.cpp
        ${lang_includes}
)

add_executable(disasm
        cpp/disassembler/main.cpp
        cpp/disassembler/disassembler.cpp
        ${lang_includes}
)

add_executable(exec
        cpp/executor/main.cpp
        cpp/executor/executor.cpp
        cpp/disassembler/disassembler.cpp
        ${lang_includes}
)

add_executable(interp
        cpp/interpreter/main.cpp
        cpp/executor/executor.cpp
        ${lang_includes}
)

add_compile_definitions(LOG_LEVEL=LVL_DEBUG_2)
