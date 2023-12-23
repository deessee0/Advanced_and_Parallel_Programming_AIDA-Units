CC = gcc
CFLAGS = -O3 -Wall -pedantic -std=c17 -fno-if-conversion -fno-if-conversion2 -fno-tree-loop-if-convert

all: branch branchless

branch: branch.c
	${CC} ${CFLAGS} -o $@ $<

branchless: branchless.c
	${CC} ${CFLAGS} -o $@ $<
