struct stat {
  int min;
  int max;
  float avg;
};

struct stat compute_stats(int * v, int len);
