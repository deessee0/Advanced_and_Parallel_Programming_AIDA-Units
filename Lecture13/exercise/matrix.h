#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdbool.h>

float * make_random_matrix(int n);

float * make_zero_matrix(int n);

float * to_column_major(float * M, int n);

void print_matrix(float * M, int n, bool column_major);

#endif
