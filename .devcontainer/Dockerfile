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
    chmod +x run.sh

CMD ["./run.sh"]