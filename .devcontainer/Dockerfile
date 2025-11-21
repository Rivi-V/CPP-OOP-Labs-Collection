FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libgtest-dev \
    googletest \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY . .

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
    chmod +x run.sh

CMD ["./run.sh"]