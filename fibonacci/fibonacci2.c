#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int total_ready_tasks;
int max_task;
int max_level;
void fib_static_wrap(int n, int level, long long *x);
long long fib(int n, int level);
long long fib_seq(int n);

int main(int argc, char *argv[])
{
  int n, num_threads;
  long long result, result_seq;
  double start, t_seq, t_pll;

  // total numbers
  n = atoi(argv[1]);
  // how many threads
  num_threads = atoi(argv[2]);
  // cut off level, 4 or 8
  max_level = atoi(argv[3]);

  total_ready_tasks = 0;
  
  //seq
  start = omp_get_wtime();

  result_seq = fib_seq(n);

  t_seq = omp_get_wtime() - start;

  omp_set_num_threads(num_threads);

  start = omp_get_wtime();

  #pragma omp parallel
  {
    #pragma omp single nowait
    #pragma omp task untied
    result = fib(n, 0);
  }

  t_pll = omp_get_wtime() - start;

  printf("The fibonacci of %d seq is %lld \n\t\t pll is %lld\n", n, result_seq, result);
  printf("Sequential: %f \n", t_seq);
  printf("Parallel: %f \n", t_pll);
  printf("Speed up: %f\n", t_seq / t_pll);
}

long long fib_seq(int n)
{
  long long x, y;

  if (n < 2) return n;

  x = fib_seq(n - 1);
  y = fib_seq(n - 2);
  
  return (x + y);
}

long long fib(int n, int level)
{
  long long x, y;

  if (n < 2)  return n;

  fib_static_wrap(n - 1, level + 1, &x);
  fib_static_wrap(n - 2, level + 1, &y);

  #pragma omp taskwait
  return (x + y);

}

void fib_static_wrap(int n, int level, long long *x)
{
  if (level <= max_level)
  {
    #pragma omp task untied
    {
      *x = fib(n, level);
    }
  }
  else
  {
    *x = fib_seq(n);
  }
}