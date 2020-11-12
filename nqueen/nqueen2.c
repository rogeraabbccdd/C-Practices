#include <stdio.h>
//#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>
#include <string.h>
#include <stdbool.h>

int queen[25], sols;
int place(int, int);
int abs(int);
bool print = false;

void n_queens(int k, int n)
{
  int r, w, i, j;
  int l = 1;
  for (i = 1; i <= n; i++)
  {
    if (place(k, i) == 1)
    {
      queen[k] = i;
      if (k == n)
      {
        if (l == 1)
        {
          //printf("Pictorial solution to %d QUEENS PROBLEM:\n",n);
          l++;
          if(print) {
            for (r = 1; r <= n; r++)
            {
              for (w = 1; w <= n; w++)
              {
                if (w != queen[r])
                  printf(" *");
                else
                  printf(" Q");
              }
              printf("\n");
            }
            printf("Other solutions:\n");
          }
        }
        for (j = 1; j <= n; j++) //printf(" %d",queen[j]);
          //printf("\n");
          sols++;
      }
      else
        n_queens(k + 1, n);
    }
  }
}

int place(int k, int i)
{
  int j;
  for (j = 1; j < k; j++)
  {
    if ((queen[j] == i) || ((abs(queen[j] - i)) == (abs(j - k))))
    {
      return 0;
    }
  }
  return 1;
}

void n_queens2(int k, int n)
{
  int r, w, i, j;
  int l2 = 1;

  // No omp for here because this is recursive function.
  for (i = 1; i <= n; i++)
  {
    int p = place(k, i);

    if (p == 1)
    {
      queen[k] = i;

      if (k == n)
      {
        if (l2 == 1)
        {
          //printf("Pictorial solution to %d QUEENS PROBLEM:\n",n);
          #pragma omp atomic
          l2++;

          if(print) {
            for (r = 1; r <= n; r++)
            {
              for (w = 1; w <= n; w++)
              {
                if (w != queen[r])
                  printf(" *");
                else
                  printf(" Q");
              }
              printf("\n");
            }
            printf("Other solutions:\n");
          }
        }
        for (j = 1; j <= n; j++) {
          //printf(" %d",queen[j]);
          //printf("\n");
          #pragma omp atomic
          sols++;
        }
      }
      else
        #pragma omp task shared (i)
        n_queens2(k + 1, n);
    }
    // This will make program slower
    // 2.x -> 1.5
    // #pragma omp taskwait
  }
}

int abs(x)
{
  if (x < 0)
    return (-x);
  else
    return x;
}

void main(int argc, char *argv[])
{
  int num = atoi(argv[1]);
  print = argc == 3 && strcmp(argv[2], "print") == 0;

  double start_time, run_time, sequential_time, parallel_time;

  if (num > 24)
  {
    printf("Maximum of Queen 24 only: you have exceeded the limit\n");
    exit(0);
  }

  // clrscr();
  printf("N - QUEENS PROBLEM\n");


  printf("All possible placements of %d queens\n", num);

  printf("=== Sequential ===\n");

  start_time = omp_get_wtime();

  n_queens(1, num);

  run_time = omp_get_wtime() - start_time;
  sequential_time = run_time;
  
  printf("Total number of solutions: %d\n", sols);

  // Reset
  sols = 0;
  memset(queen, 0, 25);

  printf("=== Parallel ===\n");

  start_time = omp_get_wtime();
  n_queens2(1, num);
  run_time = omp_get_wtime() - start_time;
  parallel_time = run_time;

  printf("Total number of solutions: %d\n", sols);

  // Print Results
  printf("=== Result ===\n");
  printf("The Sequential time is %f\n", sequential_time);
  printf("The Parallel time is %f\n", parallel_time);
  printf("The speedup of the program is %f\n", sequential_time / parallel_time);

  //getch();
}