cmake_minimum_required(VERSION 3.10)

project(oop_7 
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 7: Многопоточная симуляция боев NPC"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

# Находим GoogleTest
find_package(GTest REQUIRED)

# Находим все исходные файлы
file(GLOB LIBRARY_SOURCES 
    ${SOURCE_DIR}/*.cpp
)

# Основная программа
add_executable(npc_simulator
    main.cpp
    ${LIBRARY_SOURCES}
)

# Тестовая программа
add_executable(npc_tests
    test/tests01.cpp
    ${LIBRARY_SOURCES}
)

target_link_libraries(npc_tests PRIVATE 
    GTest::gtest 
    GTest::gtest_main
)

# Настройки компилятора
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(npc_simulator PRIVATE -Wall -Wextra -Wpedantic -pthread)
    target_compile_options(npc_tests PRIVATE -Wall -Wextra -Wpedantic -pthread)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(npc_simulator PRIVATE /W4)
    target_compile_options(npc_tests PRIVATE /W4)
endif()

set(CMAKE_BUILD_TYPE RelWithDebInfo)