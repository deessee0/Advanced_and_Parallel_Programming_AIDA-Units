#!/bin/sh

gcc -c stat.c
ar r libstat.a stat.o
ranlib libstat.a
gcc -L. -o main main.c -lstat
