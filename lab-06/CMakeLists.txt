cmake_minimum_required(VERSION 3.15)

project(lab_06
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 6 - Паттерны проектирования"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    cmake_policy(SET CMP0135 NEW)
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Основная библиотека
add_library(lab_06_lib STATIC
    ${SOURCE_DIR}/npc.cpp
    ${SOURCE_DIR}/dragon.cpp
    ${SOURCE_DIR}/elf.cpp
    ${SOURCE_DIR}/knight_errant.cpp
    ${SOURCE_DIR}/observer.cpp
    ${SOURCE_DIR}/factory.cpp
)

target_include_directories(lab_06_lib PUBLIC ${INCLUDE_DIR})

# Основной исполняемый файл
add_executable(lab_06_exe main.cpp)
target_link_libraries(lab_06_exe PRIVATE lab_06_lib)

# Опция для сборки тестов
option(BUILD_TESTS "Build Google Tests" OFF)

if(BUILD_TESTS)
    # Ищем GoogleTest
    find_package(GTest REQUIRED)
    
    # Исполняемый файл для тестов
    add_executable(lab_06_tests test/tests01.cpp)
    target_link_libraries(lab_06_tests PRIVATE lab_06_lib GTest::gtest GTest::gtest_main)
    
    # Добавляем возможность запуска тестов через CTest
    include(GoogleTest)
    gtest_discover_tests(lab_06_tests)
    
    message(STATUS "Google Tests will be built")
endif()

# Настройки компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lab_06_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab_06_exe PRIVATE -Wall -Wextra -Wpedantic)
    
    if(BUILD_TESTS)
        target_compile_options(lab_06_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(lab_06_lib PRIVATE /W4)
    target_compile_options(lab_06_exe PRIVATE /W4)
    
    if(BUILD_TESTS)
        target_compile_options(lab_06_tests PRIVATE /W4)
    endif()
endif()

# Установка типа сборки по умолчанию
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Тип сборки" FORCE)
endif()

message(STATUS "Тип сборки: ${CMAKE_BUILD_TYPE}")
message(STATUS "Сборка тестов: ${BUILD_TESTS}")

# Современный способ установки свойств
set_target_properties(lab_06_exe PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Установка выходных директорий
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Для тестов также устанавливаем выходную директорию
if(BUILD_TESTS)
    set_target_properties(lab_06_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()