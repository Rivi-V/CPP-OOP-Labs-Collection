FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential cmake git \
    libgtest-dev google-mock \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY . .

# Сборка основного проекта
RUN cmake -B build && cmake --build build

# Собираем тесты С GoogleTest библиотеками (ВЕРНУЛИ ФЛАГИ!)
RUN g++ -std=c++17 -I./include \
    src/Twelve.cpp test/tests01.cpp \
    -lgtest -lgtest_main -lpthread \
    -o build/tests

RUN echo '#!/bin/bash' > run.sh
RUN echo 'echo \"=== Running Google Tests ===\"' >> run.sh
RUN echo './build/tests' >> run.sh
RUN echo 'echo \"\"' >> run.sh
RUN echo 'echo \"=== Running Main Demo ===\"' >> run.sh
RUN echo './build/lab_02_exe' >> run.sh

RUN chmod +x run.sh
CMD ["./run.sh"]