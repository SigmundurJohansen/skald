FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    clang \
    libmicrohttpd-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/skald
COPY . .
RUN g++ --std=c++17 -o skald main.cpp src/file_system.cpp src/makefile.cpp external/yyjson.c src/json_reader.cpp src/default_project.cpp
RUN mv ./skald /usr/bin/
