#!/bin/sh

set -xe

CC=gcc
INC="-I include"
CFLAGS="-ggdb -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -fsanitize=address -fsanitize=undefined"
LIBS="-lraylib -lGL -lm -pthread -ldl -lrt -lX11"
SRC="src/main.c src/game.c src/laser.c src/ring_buffer.c src/meteor.c"

mkdir -p ./build/
export ASAN_OPTIONS=fast_unwind_on_malloc=false

$CC $INC $CFLAGS -o ./build/main $SRC $LIBS
