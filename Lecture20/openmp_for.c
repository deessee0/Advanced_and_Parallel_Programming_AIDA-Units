#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int * random_vector(int len)
{
  int * v = (int *)malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    v[i] = rand() % 10;
  }
  return v;
}

int main(int argc, char *argv[])
{
  const int n = 1<<20;
  int * v = random_vector(n);
  int sum = 0;

#pragma omp parallel
  {
    int partial = 0;
#pragma omp for nowait
    for (int i = 0; i < n; i++) {
      partial += v[i];
    }
#pragma omp critical
    {
      sum += partial;
    }
  }
  printf("Con somme parziali e sezione critica la somma è %d\n", sum);

  sum = 0;
#pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
    sum += v[i];
  }

  printf("Con reduction la somma è %d\n", sum);


  // Versione sbagliata, accesso alla variablie condivisa
  // non controlalto, c'è una race condition
  sum = 0;
#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    sum += v[i];
  }

  printf("Senza sezione critica la somma è %d\n", sum);
  
  return 0;
}
