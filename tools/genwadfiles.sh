#!/usr/bin/env bash

set -e
echo Compiling compressor
gcc -o tools/compress_wad tools/compress_wad.c src/miniz.c -Iinclude
echo Compressing
./tools/compress_wad
echo Converting to c header file
xxd -i res/doom1.zlib > include/doom1wad.h
