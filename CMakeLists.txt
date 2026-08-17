cmake_minimum_required(VERSION 4.3)

project(ELF_Parser C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ELF_Parser
    src/main.c
)

target_include_directories(ELF_Parser
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
