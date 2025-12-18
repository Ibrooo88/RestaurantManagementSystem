FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

RUN apt-get update && \
    apt-get install -y \
    tzdata \
    build-essential \
    cmake \
    ninja-build \
    qtbase5-dev \
    qt5-qmake \
    qtdeclarative5-dev \
    qttools5-dev \
    qttools5-dev-tools \
    libsqlite3-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -B build -S . -G "Ninja"
RUN cmake --build build

CMD ["./build/bin/RestaurantManagementSystem"]
