#include <stdlib.h>
#include <math.h>

#include "graph.h"

void shortcut_std(float * m, float * d, int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      m[i * n + j] = INFINITY;
      for (int k = 0; k < n; k++) {
	float tmp = d[i * n + k] + d[k * n + j];
	if (tmp < m[i * n + j]) {
	  m[i * n + j] = tmp;
	}
      }
    }
  }
}

void shortcut_trs(float * m, float * d, int n)
{
  float * t = (float *)malloc(n * n * sizeof(float));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      t[j * n + i] = d[i * n + j];
    }
  }
 
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      m[i * n + j] = INFINITY;
      for (int k = 0; k < n; k++) {
	float tmp = d[i * n + k] + t[j * n + k];
	if (tmp < m[i * n + j]) {
	  m[i * n + j] = tmp;
	}
      }
    }
  }
  
  free(t);
}

void shortcut_omp(float * m, float * d, int n)
{
#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      m[i * n + j] = d[i * n + j];
      for (int k = 0; k < n; k++) {
	float tmp = d[i * n + k] + d[k * n + j];
	if (tmp < m[i * n + j]) {
	  m[i * n + j] = tmp;
	}
      }
    }
  }
}

void shortcut(float * m, float * d, int n)
{
  float * t = (float *)malloc(n * n * sizeof(float));
#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      t[j * n + i] = d[i * n + j];
    }
  }
  
#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      m[i * n + j] = d[i * n + j];
      for (int k = 0; k < n; k++) {
	float tmp = d[i * n + k] + t[j * n + k];
	if (tmp < m[i * n + j]) {
	  m[i * n + j] = tmp;
	}
      }
    }
  }
  free(t);
}
