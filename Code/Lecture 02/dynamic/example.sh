#!/bin/sh

gcc -fPIC -c stat.c
# for Linux use libstat.so
gcc -o libstat.dylib -shared stat.o
gcc -o main main.c -L. -lstat

# proviamo a spostare dove si trova la libreria
mkdir -p lib
mv libstat.dylib lib/

# for Linux use LD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=./lib/:$DYL_LIBRARY_PATH
./main
