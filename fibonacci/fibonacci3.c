#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
long long fib(int n);
long long fib2(int n);

long long fib(int n)
{
  if (n == 0) return 0;
  else if (n == 1)  return 1;
  else return (fib(n - 1) + fib(n - 2));
}

long long fib2(int n)
{
  long long result;
  int i;

  if (n == 0) result = 0;
  else if (n == 1) result = 1;
  else {
    #pragma omp parallel
    {
      int i,j;

      #pragma omp task shared(i)
      i = fib(n - 1);

      #pragma omp task shared(j)
      j = fib(n - 2);

      #pragma omp taskwait
      result = i + j;
    }
  }

  return result;
}

int main(int argc, char *argv[])
{
  double start_time, run_time, sequential_time, parallel_time;

  int i;
  int input = atoi(argv[1]);

  long long fibnum1, fibnum2;

  start_time = omp_get_wtime();

  fibnum1 = fib(input);

  run_time = omp_get_wtime() - start_time;

  sequential_time = run_time;

  start_time = omp_get_wtime();

  fibnum2 = fib2(input);

  run_time = omp_get_wtime() - start_time;
  parallel_time = run_time;

  // Print Results
  printf("=== Result ===\n");
  printf("Sequential: %lld, time is %f\n", fibnum1, sequential_time);
  printf("Parallel: %lld, time is %f\n", fibnum2, parallel_time);
  printf("The speedup of the program is %f\n", sequential_time / parallel_time);

  return 0;
}