CC = gcc
HEADERS = ${wildcard *.h}
LIB = lib
SHARED_EXT=dylib
STATIC = yes
ifeq "${STATIC}" "yes"
	CFLAGS = -O3 -Wall -pedantic -std=c17
else
	CFLAGS = -fPIC -O3 -Wall -pedantic -std=c17
endif

all: main

ifeq "${STATIC}" "yes"
main: main.o ${LIB}/libbst.a
	${CC} ${CFLAGS} -o $@ $< -L./${LIB} -lbst
else
main: main.o ${LIB}/libbst.${SHARED_EXT}
	${CC} ${CFLAGS} -o $@ $< -L./${LIB} -lbst
endif

${LIB}/libbst.a: bst.o tree_node.o print_tree.o
	mkdir -p ${LIB}
	ar rs $@ $^

${LIB}/libbst.${SHARED_EXT}: bst.o tree_node.o print_tree.o
	${CC} ${CFLAGS} -o $@ -shared $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -rf ${LIB}/*.a  ${LIB}/*.${SHARED_EXT}
	rmdir -p ${LIB}
	rm main
