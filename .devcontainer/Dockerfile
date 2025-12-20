FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Устанавливаем необходимые пакеты
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libgtest-dev \
    googletest \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY . .

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
    chmod +x run.sh

CMD ["./run.sh"]