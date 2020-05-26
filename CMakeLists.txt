cmake_minimum_required(VERSION 3.9)
project(SPL_Compiler)
set(CMAKE_CXX_STANDARD 14)

find_package(FLEX REQUIRED)
message(STATUS "Found FLEX ${FLEX_VERSION}")
find_package(BISON REQUIRED)
message(STATUS "Found BISON ${BISON_VERSION}")
BISON_TARGET(parser
        parser.y
        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(lexer
        lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument -Wno-deprecated-register")

add_executable(splc main.cpp AST.h AST.cpp parser.hpp codegen.cpp codegen.h SystemFunctions.cpp ConstTable.h
        ${FLEX_lexer_OUTPUTS}
        ${BISON_parser_OUTPUTS}
#        parser.cpp
#        lexer.cpp
        )

target_link_libraries(splc "-lLLVM-9")  # fixme: auto detect llvm version
target_include_directories(splc
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${FLEX_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR})


add_custom_command(TARGET splc
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/system.spl ${CMAKE_CURRENT_BINARY_DIR})