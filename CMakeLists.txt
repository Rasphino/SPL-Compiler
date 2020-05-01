cmake_minimum_required(VERSION 3.10)
project(tiny_compiler)

set(CMAKE_CXX_STANDARD 14)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)


BISON_TARGET(tiny_parser
            tiny_parser.yy
            ${CMAKE_CURRENT_BINARY_DIR}/tiny_parser.tab.cc)
FLEX_TARGET(tiny_lexer
            tiny_lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/tiny_lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(tiny_lexer tiny_parser)

add_executable(tiny_compiler
        main.cpp
        Driver.cpp
        ${FLEX_tiny_lexer_OUTPUTS}
        ${BISON_tiny_parser_OUTPUTS})

target_include_directories(tiny_compiler
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${FLEX_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR})