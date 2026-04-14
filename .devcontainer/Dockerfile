FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

<<<<<<< HEAD
=======
# Устанавливаем необходимые пакеты
>>>>>>> temp_oop_7/main
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libgtest-dev \
    googletest \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY . .

<<<<<<< HEAD
<<<<<<< HEAD
RUN echo "=== Project Structure ===" && \
    find . -name "*.cpp" -o -name "*.h" | sort

# Собираем основной проект
RUN cmake -B build -DCMAKE_CXX_STANDARD=17 && \
    cmake --build build

# Собираем тесты, включая необходимые исходные файлы
RUN if [ -f "test/tests01.cpp" ]; then \
        echo "Building tests from test/tests01.cpp" && \
        g++ -std=c++17 -I./include \
            test/tests01.cpp \
            src/fixed_block_memory_resource.cpp \
            -lgtest -lgtest_main -lpthread \
            -o build/tests; \
    elif [ -f "tests01.cpp" ]; then \
        echo "Building tests from tests01.cpp" && \
        g++ -std=c++17 -I./include \
            tests01.cpp \
            src/fixed_block_memory_resource.cpp \
            -lgtest -lgtest_main -lpthread \
            -o build/tests; \
    else \
        echo "No test file found" && exit 1; \
    fi

# Создаем скрипт запуска
RUN echo '#!/bin/bash' > run.sh && \
    echo 'echo "=== Running Google Tests ==="' >> run.sh && \
    echo 'if [ -f "build/tests" ]; then ./build/tests; else echo "No tests to run"; fi' >> run.sh && \
    echo 'echo ""' >> run.sh && \
    echo 'echo "=== Running Main Demo ==="' >> run.sh && \
    echo 'if [ -f "build/oop_5_exe" ]; then ./build/oop_5_exe; else echo "Main executable not found"; fi' >> run.sh && \
=======
# Исправляем npc.h - заменяем forward declaration на #include "observer.h"
RUN sed -i 's/class IFightObserver;/#include "observer.h"/' include/npc.h

RUN echo "=== Project Structure ===" && \
    find . -type f \( -name "*.cpp" -o -name "*.h" \) | sort

RUN mkdir -p build

RUN echo "=== Building Main Program ===" && \
    g++ -std=c++17 -I./include \
        main.cpp \
        src/npc.cpp \
        src/dragon.cpp \
        src/elf.cpp \
        src/knight_errant.cpp \
        src/factory.cpp \
        src/observer.cpp \
        -o build/lab_06_exe

RUN echo "=== Building Tests ===" && \
    g++ -std=c++17 -I./include \
        test/tests01.cpp \
        src/npc.cpp \
        src/dragon.cpp \
        src/elf.cpp \
        src/knight_errant.cpp \
        src/factory.cpp \
        src/observer.cpp \
        -lgtest -lgtest_main -lpthread \
        -o build/lab_06_tests

RUN echo "=== Checking Built Executables ===" && \
    find build -type f -executable | sort

RUN echo '#!/bin/bash' > run.sh && \
    echo 'echo "=== Running Tests ==="' >> run.sh && \
    echo 'if [ -f "build/lab_06_tests" ]; then' >> run.sh && \
    echo '    ./build/lab_06_tests' >> run.sh && \
    echo 'else' >> run.sh && \
    echo '    echo "Tests not found"' >> run.sh && \
    echo 'fi' >> run.sh && \
    echo '' >> run.sh && \
    echo 'echo ""' >> run.sh && \
    echo 'echo "=== Running Main Program ==="' >> run.sh && \
    echo 'if [ -f "build/lab_06_exe" ]; then' >> run.sh && \
    echo '    ./build/lab_06_exe' >> run.sh && \
    echo 'else' >> run.sh && \
    echo '    echo "Main program not found"' >> run.sh && \
    echo 'fi' >> run.sh && \
>>>>>>> temp_oop_6/main
=======
# Показываем структуру проекта
RUN echo "=== Project Structure ===" && \
    find . -name "*.cpp" -o -name "*.h" | sort

# Собираем основной проект через CMake
RUN cmake -B build -DCMAKE_CXX_STANDARD=17 && \
    cmake --build build --target npc_simulator

# Собираем тесты ВСЕ ВМЕСТЕ правильно
RUN echo "=== Building tests ===" && \
    g++ -std=c++17 -I./include \
        test/tests01.cpp \
        src/battle_visitor.cpp \
        src/common.cpp \
        src/dragon.cpp \
        src/elf.cpp \
        src/factory.cpp \
        src/fight_manager.cpp \
        src/helpers.cpp \
        src/knight_errant.cpp \
        src/map_printer.cpp \
        src/npc.cpp \
        src/observer.cpp \
        -lgtest -lgtest_main -lpthread \
        -o build/npc_tests || \
    (echo "=== Fallback: trying different approach ===" && \
     g++ -std=c++17 -I./include \
         test/tests01.cpp \
         src/*.cpp \
         -lgtest -lgtest_main -lpthread \
         -o build/npc_tests)

# Создаем скрипт запуска
RUN echo '#!/bin/bash' > run.sh && \
    echo 'echo "=========================================="' >> run.sh && \
    echo 'echo "🧪 ЗАПУСК GOOGLE TESTS"' >> run.sh && \
    echo 'echo "=========================================="' >> run.sh && \
    echo 'if [ -f "build/npc_tests" ]; then' >> run.sh && \
    echo '    echo "Запускаю тесты..."' >> run.sh && \
    echo '    if ./build/npc_tests --gtest_color=yes; then' >> run.sh && \
    echo '        echo ""' >> run.sh && \
    echo '        echo "=========================================="' >> run.sh && \
    echo '        echo "✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!"' >> run.sh && \
    echo '        echo "=========================================="' >> run.sh && \
    echo '        echo ""' >> run.sh && \
    echo '        echo "=========================================="' >> run.sh && \
    echo '        echo "🎮 ЗАПУСК ОСНОВНОЙ ПРОГРАММЫ"' >> run.sh && \
    echo '        echo "=========================================="' >> run.sh && \
    echo '        ./build/npc_simulator' >> run.sh && \
    echo '    else' >> run.sh && \
    echo '        echo ""' >> run.sh && \
    echo '        echo "=========================================="' >> run.sh && \
    echo '        echo "❌ ТЕСТЫ НЕ ПРОЙДЕНЫ! Основная программа не будет запущена."' >> run.sh && \
    echo '        echo "=========================================="' >> run.sh && \
    echo '        exit 1' >> run.sh && \
    echo '    fi' >> run.sh && \
    echo 'else' >> run.sh && \
    echo '    echo "Test executable not found. Building it..."' >> run.sh && \
    echo '    # Пробуем собрать тесты на лету' >> run.sh && \
    echo '    g++ -std=c++17 -I./include test/tests01.cpp src/*.cpp -lgtest -lgtest_main -lpthread -o build/npc_tests && \' >> run.sh && \
    echo '    ./build/npc_tests --gtest_color=yes && \' >> run.sh && \
    echo '    echo "✅ ТЕСТЫ ПРОЙДЕНЫ" && \' >> run.sh && \
    echo '    ./build/npc_simulator' >> run.sh && \
    echo 'fi' >> run.sh && \
>>>>>>> temp_oop_7/main
    chmod +x run.sh

CMD ["./run.sh"]