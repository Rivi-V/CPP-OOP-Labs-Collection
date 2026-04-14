cmake_minimum_required(VERSION 3.10)

project(oop_5 
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 5: Итераторы и аллокаторы"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

file(GLOB LIBRARY_SOURCES 
    ${SOURCE_DIR}/*.cpp
)

add_library(oop_5_lib ${LIBRARY_SOURCES})

add_executable(oop_5_exe main.cpp)

target_link_libraries(oop_5_exe PRIVATE oop_5_lib)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(oop_5_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(oop_5_exe PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(oop_5_lib PRIVATE /W4)
    target_compile_options(oop_5_exe PRIVATE /W4)
endif()

set(CMAKE_BUILD_TYPE RelWithDebInfo)