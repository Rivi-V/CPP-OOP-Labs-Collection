cmake_minimum_required(VERSION 3.10)

project(lab_02 
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 2: Класс Twelve"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

add_library(lab_02_lib ${LIBRARY_SOURCES})

add_executable(lab_02_exe main.cpp)

target_link_libraries(lab_02_exe PRIVATE lab_02_lib)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab_02_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab_02_exe PRIVATE -Wall -Wextra -Wpedantic)
endif()