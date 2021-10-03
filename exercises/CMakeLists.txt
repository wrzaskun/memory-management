cmake_minimum_required(VERSION 3.0)
project(memory_management)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")
file(GLOB SOURCES *.cpp)

foreach(FILE ${SOURCES})
    add_compile_options(-Wall -Wextra -pedantic -pedantic-errors -g)
    get_filename_component(BINNAME ${FILE} NAME_WE)
    add_executable(${BINNAME} ${FILE})
endforeach(FILE)
