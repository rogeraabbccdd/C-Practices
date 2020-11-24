/* serial code to compute Fibonacci */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int fib(int n)
{
  int i, j;
  if (n < 2)
    return n;
  i = fib(n - 1);
  j = fib(n - 2);
  return (i + j);
}

int fibm(int n)
{
  int i, j, id;

  if (n < 2)  return n;

  #pragma omp task shared(i)
  {
    i = fib(n - 1);
  }

  #pragma omp task shared(j)
  {
    j = fib(n - 2);
  }
  
  #pragma omp taskwait

  return (i + j);
}

int main()
{
  int n, i;
  clock_t start, stop;

  printf("Please enter the fibonacci n to calculate\n");
  scanf("%d", &n);

  //n=30; //Calculating 30 fibonacci
  printf("Now I am calculating the fibonacci in SERIAL\n\n");
  printf("============================================\n");

  start = clock();

  printf("fib(%d) = %d\n", n, fib(n));

  stop = clock();

  printf("The elapsed time it took to calculate the fib(%d) is = %10.9f\n",n,(double)(stop-start)/CLOCKS_PER_SEC);
  printf("Now I am calculating the fibonacci in OPENMP\n\n");
  printf("============================================\n");

  int nthreads,tid;

  start = clock();

  printf("fib(%d) = %d\n",n,fibm(n));

  stop = clock();

  printf("The elapsed time it took to calculate the fibm(%d) is = %10.9f\n",n,(double)(stop-start)/CLOCKS_PER_SEC);
  
  return(0);
}