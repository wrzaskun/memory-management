cmake_minimum_required(VERSION 3.0)
project(memory_management)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES *.cpp)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")

foreach(FILE ${SOURCES})   
    get_filename_component(BINNAME ${FILE} NAME_WE)
    add_executable(${BINNAME} ${FILE})
    target_compile_options(${BINNAME} PRIVATE -Wall -Wextra -pedantic -pedantic-errors -g)
    target_link_options(${BINNAME} PRIVATE -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined)
endforeach(FILE)