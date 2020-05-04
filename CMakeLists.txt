cmake_minimum_required(VERSION 3.10)
project(SPL_compiler)

set(CMAKE_CXX_STANDARD 14)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)


BISON_TARGET(SPL_parser
            SPL_parser.yy
            ${CMAKE_CURRENT_BINARY_DIR}/SPL_parser.tab.cc)
FLEX_TARGET(SPL_lexer
            SPL_lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/SPL_lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(SPL_lexer SPL_parser)

add_executable(SPL_compiler
        main.cpp
        Driver.cpp
        ${FLEX_SPL_lexer_OUTPUTS}
        ${BISON_SPL_parser_OUTPUTS})

target_include_directories(SPL_compiler
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${FLEX_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(googletest)