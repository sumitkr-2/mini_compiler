cmake_minimum_required(VERSION 3.12)
project(minic LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Search homebrew paths for newer bison if on macOS
list(PREPEND CMAKE_PROGRAM_PATH /opt/homebrew/opt/bison/bin /usr/local/opt/bison/bin)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(
    Parser
    src/parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp
)

flex_target(
    Lexer
    src/lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

add_flex_bison_dependency(Lexer Parser)

include_directories(
    include
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(
    minic
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Lexer_OUTPUTS}
    src/ast.cpp
    src/symbol_table.cpp
    src/semantic.cpp
    src/tac.cpp
    src/main.cpp
)
