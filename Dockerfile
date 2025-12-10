FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
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
    && apt-get clean

WORKDIR /app

COPY . .

RUN cmake -B build -S . -G "Ninja"
RUN cmake --build build

CMD ["./build/bin/RestaurantManagementSystem"]
