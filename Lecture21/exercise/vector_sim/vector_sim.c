#include <math.h>
#include <omp.h>

#include "vector_sim.h"

float cosine_similarity(float * v1, float * v2, int len)
{
  float sum1 = 0;
  float sum2 = 0;
  float dot = 0;
  for (int i = 0; i < len; i++) {
    sum1 += v1[i] * v1[i];
    sum2 += v2[i] * v2[i];
    dot += v1[i] * v2[i];
  }
  return dot / (sqrtf(sum1) * sqrtf(sum2));
}

int most_similar(float * v, float * M, int nrows, int ncols)
{
  int idx = -1;
  float max_sim = -INFINITY;
  for (int i = 0; i < nrows; i++) {
    float sim = cosine_similarity(v, &M[i*ncols], ncols);
    if (sim > max_sim) {
      max_sim = sim;
      idx = i;
    }
  }
  return idx;
}

int omp_most_similar(float * v, float * M, int nrows, int ncols)
{
  int idx = -1;
  float max_sim = -INFINITY;
#pragma omp parallel
  {
    int local_idx = -1;
    float local_max_sim = -INFINITY;
#pragma omp for nowait
    for (int i = 0; i < nrows; i++) {
      float sim = cosine_similarity(v, &M[i*ncols], ncols);
      if (sim > local_max_sim) {
	local_max_sim = sim;
	local_idx = i;
      }
    }
#pragma omp critical
    {
      if (local_max_sim > max_sim) {
	max_sim = local_max_sim;
	idx = local_idx;
      }
    }
  }
  return idx;
}


