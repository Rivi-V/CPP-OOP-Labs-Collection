cmake_minimum_required(VERSION 3.10)

project(lab_03  # ✅ ИСПРАВИТЬ: lab_02 -> lab_03
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 3"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)  # ✅ ИСПРАВИТЬ: 11 -> 17 (вы использовали C++17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

add_library(lab_03_lib ${LIBRARY_SOURCES})

add_executable(lab_03_exe main.cpp)

target_link_libraries(lab_03_exe PRIVATE lab_03_lib)

# ✅ ДОБАВИТЬ для Windows
if(WIN32)
    set_target_properties(lab_03_exe PROPERTIES
        SUFFIX ".exe"
    )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab_03_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab_03_exe PRIVATE -Wall -Wextra -Wpedantic)
endif()