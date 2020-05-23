cmake_minimum_required(VERSION 3.10)
project(SPL_compiler)

set(CMAKE_CXX_STANDARD 14)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)


BISON_TARGET(parser
            parser.y
            ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(lexer
            lexer.l
            ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

#add_executable(lexer
#        lexer_main.cpp
#        ${FLEX_lexer_OUTPUTS}
#        )

add_executable(SPL_compiler
        main.cpp
        ${FLEX_lexer_OUTPUTS}
        ${BISON_parser_OUTPUTS})

target_include_directories(SPL_compiler
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${FLEX_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR})
