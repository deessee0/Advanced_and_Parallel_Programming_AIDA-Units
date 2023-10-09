#!/bin/sh

gcc -O0 -o main0 main.c
gcc -O1 -o main1 main.c
gcc -O2 -o main2 main.c
gcc -O3 -o main3 main.c
gcc -O3 -march=native -o mainN main.c

./main0
./main1
./main2
./main3
./mainN
