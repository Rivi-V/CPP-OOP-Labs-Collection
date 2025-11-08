cmake_minimum_required(VERSION 3.10)

project(lab_03
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 3 - Шаблонные фигуры"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})

add_executable(lab_03 
    main.cpp
)

if(MSVC)
    target_compile_options(lab_03 PRIVATE 
        /W4
        /permissive-
    )
else()
    target_compile_options(lab_03 PRIVATE 
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

if(WIN32)
    set_target_properties(lab_03 PROPERTIES
        SUFFIX ".exe"
    )
endif()